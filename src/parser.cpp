#include <cstring>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <numeric>
#include <unordered_map>
#include <regex>

// parser
#include "resource.h"
#include "parser.h"

// MIME Types
#include "MimeTypes.h"

// C++ beautifier
#include "ReservedWords.h"

// md4c MD parser
#include "md4c-html.h"

// debug
#include <iostream>

std::string urlDecode(const std::string target)
{
	std::string percentBuf{};
	std::string response = std::accumulate(
	    target.begin(),
	    target.end(),
	    std::string{},
	    [&percentBuf](std::string response, const char ch) {
		    if (!percentBuf.empty()) {
			    if (percentBuf.length() == 3) {
				    // Try to parse
				    response += static_cast<char>(std::stoi(percentBuf.substr(1), nullptr, 16));
				    percentBuf.clear();
				    // Noow checking current character
				    if (ch == '%') {
					    percentBuf += ch;
				    }
				    else {
					    response += ch;
				    }
			    }
			    else {
				    if (ch >= '0' && ch <= '9') {
					    percentBuf += ch;
				    }
				    else if (ch >= 'a' && ch <= 'f') {
					    percentBuf += ch;
				    }
				    else if (ch >= 'A' && ch <= 'F') {
					    percentBuf += ch;
				    }
				    else {
					    // non hex char - adding everyting including '%' to result
					    response += percentBuf;
					    percentBuf.clear();
				    }
			    }
		    }
		    else if (ch == '%') {
			    percentBuf += ch;
		    }
		    else {
			    response += ch;
		    }
		    return response;
	    });

	if (!percentBuf.empty() && percentBuf.length() == 3) {
		response += static_cast<char>(std::stoi(percentBuf.substr(1), nullptr, 16));
	}

	return response;
}

Parser::Parser(const std::string& docRoot)
    : docRoot_(docRoot)
{
}

std::pair<std::string, std::variant<std::string, std::vector<uint8_t>>> Parser::parse(std::pair<std::string, std::string>&& request)
{
   bool parseResult{false};
   // First line - request type
   const char *spacePtr = strchr(request.first.c_str(), ' ');
   requestType_ = std::string(request.first.c_str(), spacePtr);

   spacePtr = strchr(++spacePtr, ' ');
   requestPath_ = urlDecode(std::string(request.first.c_str() + requestType_.length() + 1, spacePtr));

   // Validation
   if (requestPath_.empty() || requestPath_[0] != '/' || requestPath_.find("..") != std::string::npos) {
      std::string errorStr = "Invalid request: '" + requestPath_ + "'";
      return buildErrorRespnose(400, "Invalid request", errorStr);
   }

   // Check if edit command
   if (requestPath_.substr(0, 5) == "/muki") {
      return EditResult(requestPath_, request.second);
   }

   if (requestPath_ == "/") {
      requestPath_ = "/miki.html";
   }

   // In case of edit - we would add '-raw' suffix to file name
   // And would send it without MD generation
   bool rawMDFile{false};
   if (const auto rawPos = requestPath_.find("-raw", requestPath_.length() - 4, 4); rawPos != std::string::npos) {
      rawMDFile = true;
      requestPath_.erase(rawPos);
   }

   std::filesystem::path pTarget(std::filesystem::relative(docRoot_));
   pTarget += requestPath_;

   if (!std::filesystem::exists(pTarget)) {
      std::string errorStr = "Resource: " + requestPath_ + " was not found";
      return buildErrorRespnose(404, "File not found", errorStr);
   }

   if (std::filesystem::is_regular_file(pTarget)) {
      std::string extension = std::filesystem::path(pTarget).extension();
      if (const auto mimeIt = MimeTypes.find(extension); mimeIt != MimeTypes.end()) {
         const auto [ext, typePair] = *mimeIt;
         const auto [mimeType, isText] = typePair;
         if (isText) {
            // If markdown - we'll use md4c parser
            if (ext == ".md" && !rawMDFile) {
               return MDFile(pTarget);
            }
            return textFile(pTarget, mimeType);
         }
         else {
            auto binaryFileResult = binaryFile(pTarget, mimeType); 
            if (std::holds_alternative<Parser::TextResponse>(binaryFileResult)) {
               return std::get<Parser::TextResponse>(binaryFileResult);
            }
            else {
               return std::get<Parser::ByteResponse>(binaryFileResult);
            }
         }
      }
      else {
         std::cout << "MimeType not found, considering it to be text" << std::endl;
         return textFile(pTarget, "text/plain");
      }
   }
   else if (std::filesystem::is_directory(pTarget)) {
      namespace fs = std::filesystem;

      std::vector<Resource> resources;
      for (const fs::directory_entry& de : fs::directory_iterator(pTarget)) {
         resources.emplace_back(
               fs::is_directory(de) ? de.path().filename().string() : de.path().stem().string(),
               std::filesystem::relative(de, docRoot_).string(),
               fs::is_directory(de) ? 'd' : 'p'
               );
      }
      std::sort(resources.begin(), resources.end());

      std::string folderContents{};
      for (const auto& resource : resources) {
         folderContents.append(resource.asString().append(";"));
      }
      return std::make_pair(buildHeader(folderContents.length(), "text/plain"), folderContents);
   }
   else {
      std::string errorStr = "Resource type of " + requestPath_ + " is not supported";
      return buildErrorRespnose(400, "Resource type not supported", errorStr);
   }

   return std::make_pair(buildHeader(0), std::vector<uint8_t>{});
}

std::pair<std::string, std::string> Parser::buildErrorRespnose(int errorCode, const std::string& errorStr, const std::string& message) const
{
    std::stringstream bsstr;
    bsstr
    << R"(<!doctype html>
<html lang="en-gb">
<head>
<title>ERROR</title>
</head>
<body>
<h3>)"
    << message
    << R"(</h3></body></html>)";

    return std::make_pair(buildHeader(bsstr.str().length(), "text/html", errorCode, errorStr), bsstr.str());
}

std::string Parser::buildHeader(int contentLength, const std::string& contentType,  int code, const std::string& status) const
{
    std::stringstream hsstr;
    hsstr 
        << "HTTP/1.1 "
        << code << " " << status
        << R"(
Server: Miki4
Content-Type: )"
        << contentType
        << R"(
Content-Length: )"
        << contentLength
        << "\r\n\r\n";
   
    return hsstr.str();
}

void Parser::beautifyCode(std::string& payload) const
{
	const std::string codeTagOpen  = R"(<code class="language-cpp">)";
	const std::string codeTagClose = R"(</code>)";

	const std::unordered_set<std::string> validPreStrs{
	    "::", " ", "\n", "\t", "&lt;", "&gt;", "*", "&amp;", "(", ")", "{"};

	const std::unordered_set<std::string> validPostStrs{
	    "::", ";", " ", "\n", "\t", "&lt;", "&gt;", "*", "&amp;", "(", ")", ","};

	const std::string blanks{" \t\n;.,(){}:/\\<>[]!*=&+-"};

	auto snippetPos = payload.find(codeTagOpen);
	while (snippetPos != std::string::npos) {
		auto snippetTo = payload.find(codeTagClose, snippetPos + 1);
		if (snippetTo == std::string::npos) {
			std::cerr << "Should not happen at all - no closing </code> tag, leaving" << std::endl;
			return;
		}

		const auto  formatFrom = snippetPos + codeTagOpen.length();
		const auto  formatLen  = snippetTo - formatFrom;
		std::string formatMe   = payload.substr(formatFrom, formatLen);

		bool        includesFound = false;
		size_t      lastInclude   = 0;
		std::string includeLines;

		std::istringstream iss{formatMe};
		for (std::string line; std::getline(iss, line);) {
			if (line.empty()) {  // New line
				++lastInclude;
				continue;
			}

			const std::regex includeRE(R"(^#include &.*$)");
			if (std::regex_match(line, includeRE)) {
				includesFound      = true;
				auto firstSpacePos = line.find_first_of(' ');
				includeLines += "<span class=\"includes\">";
				includeLines += line.substr(0, firstSpacePos);
				includeLines += "</span><span class=\"includedfile\">";
				includeLines += line.substr(firstSpacePos);
				includeLines += "</span>\n";

				lastInclude += line.length();
				++lastInclude;
			}
			else {
				break;  // First non-include line - leaving
			}
		}

		if (includesFound) {
			includeLines += "\n";
			formatMe.erase(0, lastInclude);
		}

		size_t pos     = 0;
		size_t lastPos = 0;
		bool   isAlpha = std::isalpha(formatMe[0]);

		std::vector<std::pair<std::string, bool>> asVect;
		while (true) {
			pos = (isAlpha ? formatMe.find_first_of(blanks, pos)
			               : formatMe.find_first_not_of(blanks, pos));
			if (pos == std::string::npos) {
				asVect.push_back(std::make_pair(formatMe.substr(lastPos), isAlpha));
				break;
			}
			asVect.push_back(std::make_pair(formatMe.substr(lastPos, pos - lastPos), isAlpha));
			isAlpha = !isAlpha;
			lastPos = pos;
		}

		std::vector<std::reference_wrapper<std::pair<std::string, bool>>> candidates;
		std::copy_if(
		    asVect.begin(), asVect.end(), std::back_inserter(candidates), [](const auto& el) {
			    return el.second;
		    });

		bool needReplacement = false;
		for (const auto& [tag, resvwords] : CPPFormatting) {
			std::string cssClass{"<span class=\""};
			cssClass.append(tag).append("\">");

			for (const auto& resvW : resvwords) {
				const auto candidatePred([&resvW](const auto& el) {
					return el.get().first == resvW;
				});

				auto foundIt = std::find_if(candidates.begin(), candidates.end(), candidatePred);
				while (foundIt != candidates.end()) {
					needReplacement = true;
					foundIt->get().first.insert(0, cssClass);
					foundIt->get().first.append("</span>");
					foundIt->get().second = false;

					candidates.erase(foundIt);

					foundIt = std::find_if(candidates.begin(), candidates.end(), candidatePred);
				}
			}
		}

		if (needReplacement || includesFound) {
			std::string formatted;
			if (needReplacement) {
				formatted = std::accumulate(asVect.begin(),
				                            asVect.end(),
				                            std::string{},
				                            [](std::string& result, const auto& ve) {
					                            result += ve.first;
					                            return result;
				                            });
			}

			if (includesFound) {
				formatted.insert(0, includeLines);
			}

			payload.replace(formatFrom, formatLen, formatted);
			snippetTo = formatFrom + formatted.length();
		}

		// snippedTo must me amended if changes were done
		snippetPos = payload.find(codeTagOpen, snippetTo);
	}
}

Parser::TextResponse Parser::textFile(const std::filesystem::path& pTarget, const std::string& mimeType) const
{
   if (std::ifstream ifs(pTarget); ifs) {
      std::string fileContents(
            (std::istreambuf_iterator<char>(ifs)),
            (std::istreambuf_iterator<char>()));

      return std::make_pair(buildHeader(fileContents.length(), mimeType), fileContents);
   }
   std::string errorStr{"Cannot read: "};
   errorStr += pTarget;

   return buildErrorRespnose(404, "Not found", errorStr);
}

std::variant<Parser::ByteResponse, Parser::TextResponse> Parser::binaryFile(const std::filesystem::path& pTarget, const std::string& mimeType) const
{
   if (std::ifstream ifs(pTarget, std::ios::in|std::ios::binary); ifs) {
      ifs.unsetf(std::ios::skipws); // Stop eating new lines
      ifs.seekg(0, std::ios::end);
      std::streampos fileSize = ifs.tellg();
      ifs.seekg(0, std::ios::beg);

      std::vector<uint8_t> buffer(fileSize);
      if (ifs.read(reinterpret_cast<char*>(buffer.data()), fileSize)) {
         std::cout << "Read successfully into vector " << buffer.size() << " bytes";
         return std::make_pair(buildHeader(buffer.size(), mimeType), buffer);
      }
      else {
         std::string errorStr{"Failed to read data into buffer"};
         return buildErrorRespnose(500, "Read error", errorStr);
      }
   }
   std::string errorStr{"Cannot read: "};
   errorStr += pTarget;

   return buildErrorRespnose(500, "Read error", errorStr);
}

Parser::TextResponse Parser::MDFile(const std::filesystem::path& pTarget) const
{
   if (std::ifstream ifs(pTarget); ifs) {
      std::string htmlIn(
            (std::istreambuf_iterator<char>(ifs)),
            std::istreambuf_iterator<char>());

      // Paser flags, for now switching everything on GitHub behaviour
      unsigned parser_flags = MD_DIALECT_GITHUB; // See md4c.h:333 

      // Render flags
      unsigned render_flags = MD_HTML_FLAG_DEBUG | MD_HTML_FLAG_SKIP_UTF8_BOM;

      // Parse buffer
      std::string htmlOutput{};

      int result = md_html(
            htmlIn.c_str(),  // MarkDown Source
            htmlIn.length(), // MarkDown Source lenght
            [](const char* chPtr, unsigned size, void* pv) {  // Callback which will be called on each chunk processed
            reinterpret_cast<std::string*>(pv)->append(chPtr, size);
            },
            reinterpret_cast<void*>(&htmlOutput), // will be propagated back to above process_output() callback as void* pv
            parser_flags,                         // parser flags
            render_flags                          // render flags (MD_HTML_FLAG_xxxx) , just 4 of them
            );
      beautifyCode(htmlOutput);

      return std::make_pair(buildHeader(htmlOutput.length(), "text/html"), htmlOutput);
   }
   // Something wrong
   std::string errorStr{"Cannot read: "};
   errorStr += pTarget;

   return buildErrorRespnose(404, "Not found", errorStr);
}

Parser::TextResponse Parser::EditResult(const std::string& requestPath, const std::string& requestBody) const
{
   // disassembling command
   if (std::count(requestPath.begin(), requestPath.end(), '/') < 3) {
      std::string errorText{"ERROR: Command does not have enough parameters"};
      return buildErrorRespnose(500, "Edit Failed", errorText);
   }
   std::string editCommand{requestPath};

   // removing /muki/
   editCommand.erase(0, 6);
   const auto        commandEnd = editCommand.find_first_of("/");
   const std::string command    = editCommand.substr(0, commandEnd);
   const std::string targetPath = editCommand.substr(commandEnd);
   const std::string payload    = requestBody;

   using commandHelper = std::optional<std::string> (Parser::*)(const std::string&, const std::string&) const;
   const std::map<const std::string, commandHelper> commandsMap {
        {"add", &Parser::addEntry}
      , {"rm", &Parser::rmEntry}
      , {"edit", &Parser::editEntry}
   };

   if (const auto cmdIt = commandsMap.find(command); cmdIt == commandsMap.end()) {
      // Report error
      std::string errorText{"ERROR: Command : '"};
      errorText.append(command).append("' not supported");
      return buildErrorRespnose(500, "Edit Failed", errorText);
   }
   else {
      const auto commandResult = std::invoke(cmdIt->second, this, targetPath, payload);
      if (commandResult.has_value()) {
         std::string errorStr{"Error occurred whilst executing: "};
         errorStr.append(command).append(", Message: ").append(*commandResult);

         return buildErrorRespnose(500, "Edit Failed", errorStr);
      }
      else {
         std::string okStr{"ok"};
         return std::make_pair(buildHeader(okStr.length(), "text/html"), okStr);
      }
   }

   return buildErrorRespnose(500, "Not implemented yet", "");
}

std::optional<std::string> Parser::rmEntry(const std::string& path, const std::string&) const
{
	// Remove entry, if not exists - return error
   std::filesystem::path pTarget(std::filesystem::relative(docRoot_));
   pTarget += path;

	if (std::filesystem::exists(pTarget)) {
		std::error_code ec;
		if (!std::filesystem::remove(pTarget, ec)) {
         std::stringstream sstr;
         sstr 
            << "Failed to remove '"
            << path
            << "', error message: '"
            << ec.message()
            << "'";

         return sstr.str();
		}
	}
	else {
      std::stringstream sstr;
      sstr 
         << "Remove candidate '"
         << path
         << "' not found";

      return sstr.str();
	}

	return {};
}

std::optional<std::string> Parser::addEntry(const std::string& path, const std::string& data) const
{
	// Add entry, if wrong path - return error
   std::filesystem::path pTarget(std::filesystem::relative(docRoot_));
   pTarget += path;

	std::filesystem::path pTargetDirectory = pTarget;
	pTargetDirectory.remove_filename();

	std::error_code ec;
	if (!std::filesystem::create_directories(pTargetDirectory, ec) && ec.value() != 0) {
      std::stringstream sstr;
      sstr 
         << "Failed create destination directory '"
         << pTarget.string()
         << "', error message: '"
         << ec.message()
         << "'";

      return sstr.str();
	}

	std::ofstream addedEntry(pTarget.string(), std::ios::out);
	if (!addedEntry) {
      std::stringstream sstr;
      sstr 
         << "Failed to open '"
         << pTarget.string()
         << "' for writting";

      return sstr.str();
	}

	addedEntry.write(data.c_str(), data.length());
	addedEntry.flush();
	addedEntry.close();

	return {};
}

std::optional<std::string> Parser::editEntry(const std::string& path, const std::string& data) const
{
	// Replace entry, if wrong path - return error
   std::filesystem::path pTarget(std::filesystem::relative(docRoot_));
   pTarget += path;

	if (!std::filesystem::exists(pTarget)) {
      std::stringstream sstr;
      sstr 
         << "Failed to find '"
         << pTarget.string()
         << "' for editing";

      return sstr.str();
	}

	std::ofstream edittedEntry(pTarget, std::ios::out | std::ios::trunc);
	if (!edittedEntry) {
      std::stringstream sstr;
      sstr
         << "Failed to open '"
         << pTarget.string()
         << "' for writting";

      return sstr.str();
	}

	edittedEntry.write(data.c_str(), data.length());
	edittedEntry.flush();
	edittedEntry.close();

	return {};
}
