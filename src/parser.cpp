#include <cstring>
#include <fstream>
#include <sstream>
#include <algorithm>

// parser
#include "resource.h"
#include "parser.h"

// md4c MD parser
#include "md4c-html.h"

// debug
#include <iostream>

// extension => {mime_type:isText}
const std::unordered_map<std::string, std::pair<const char*, bool>> MimeTypes{
    {".htm", {"text/html", true}},
    {".html", {"text/html", true}},
    {".md", {"text/html", true}},
    {".php", {"text/html", true}},
    {".css", {"text/css", true}},
    {".txt", {"text/plain", true}},
    {".js", {"application/javascript", true}},
    {".json", {"application/json", true}},
    {".xml", {"application/xml", true}},
    {".swf", {"application/x-shockwave-flash", false}},
    {".wasm", {"application/wasm", false}},
    {".flv", {"video/x-flv", false}},
    {".png", {"image/png", false}},
    {".jpe", {"image/jpeg", false}},
    {".jpeg", {"image/jpeg", false}},
    {".jpg", {"image/jpeg", false}},
    {".gif", {"image/gif", false}},
    {".bmp", {"image/bmp", false}},
    {".ico", {"image/vnd.microsoft.icon", false}},
    {".tiff", {"image/tiff", false}},
    {".tif", {"image/tiff", false}},
    {".svg", {"image/svg+xml", false}},
    {".svgz", {"image/svg+xml", false}}};

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
    requestPath_ = std::string(request.first.c_str() + requestType_.length() + 1, spacePtr);

    // Validation
    if (requestPath_.empty() || requestPath_[0] != '/' || requestPath_.find("..") != std::string::npos) {
       std::string errorStr = "Invalid request: '" + requestPath_ + "'";
       return buildErrorRespnose(400, "Invalid request", errorStr);
    }

    if (requestPath_ == "/") {
       requestPath_ = "/miki.html";
    }

    std::filesystem::path pTarget(std::filesystem::current_path());
    pTarget += "/";
    pTarget += docRoot_;
    pTarget += requestPath_;

    // Debug
    std::cout << "\nRelative request path: " << pTarget << std::endl;

    if (!std::filesystem::exists(pTarget)) {
       std::string errorStr = "Resource: " + requestPath_ + " was not found";
       return buildErrorRespnose(404, "File not found", errorStr);
    }

    if (requestType_ == "GET") {
       if (std::filesystem::is_regular_file(pTarget)) {
          std::string extension = std::filesystem::path(pTarget).extension();
          if (const auto mimeIt = MimeTypes.find(extension); mimeIt != MimeTypes.end()) {
             const auto [ext, typePair] = *mimeIt;
             const auto [mimeType, isText] = typePair;
             if (isText) {
                // If markdown - we'll use md4c parser
                if (ext == ".md") {
                   if (std::ifstream ifs(pTarget); ifs) {
                      std::string htmlIn(
                            (std::istreambuf_iterator<char>(ifs)),
                            std::istreambuf_iterator<char>());

                      // Paser flags, for now switching everything on GitHub behaviour
                      unsigned parser_flags = MD_DIALECT_GITHUB; // See md4c.h:333 

                      // Render flags
                      unsigned render_flags = MD_HTML_FLAG_DEBUG | MD_HTML_FLAG_SKIP_UTF8_BOM;

                      // Parse buffer
                      char chBUF[ 8192 ];
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


                      return std::make_pair(buildHeader(htmlOutput.length(), "text/html"), htmlOutput);
                   }
                   else {
                      std::string errorStr{"Cannot read: "};
                      errorStr += pTarget;

                      return buildErrorRespnose(404, "Not found", errorStr);
                   }
                }
                else if (std::ifstream ifs(pTarget); ifs) {
                   std::string fileContents(
                         (std::istreambuf_iterator<char>(ifs)),
                         (std::istreambuf_iterator<char>()));

                   return std::make_pair(buildHeader(fileContents.length(), mimeType), fileContents);
                }
                else {
                   std::string errorStr{"Cannot read: "};
                   errorStr += pTarget;

                   return buildErrorRespnose(404, "Not found", errorStr);
                }
             }
             else {
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
                else {
                   std::string errorStr{"Cannot read: "};
                   errorStr += pTarget;

                   return buildErrorRespnose(500, "Read error", errorStr);
                }
             }
          }
          else {
             std::cout << "MimeType not found, considering it to be binary" << std::endl;
          }
       }
       else if (std::filesystem::is_directory(pTarget)) {
          namespace fs = std::filesystem;

          std::vector<Resource> resources;
          for (const fs::directory_entry& de : fs::directory_iterator(pTarget)) {
             resources.emplace_back(
                   fs::is_directory(de) ? de.path().filename().string() : de.path().stem().string(),
                   de.path().relative_path().string(),
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
