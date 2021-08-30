#include "parser.h"
#include <cstring>
#include <fstream>
#include <sstream>

// debug
#include <iostream>

// maddy
#include <maddy/parser.h>

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

Parser::Parser(const std::string& root)
    : siteRoot_(root)
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

    if (requestType_ == "GET") {
        requestPath_.insert(0, std::filesystem::current_path());
        if (std::filesystem::exists(requestPath_) && std::filesystem::is_regular_file(requestPath_)) {
            std::string extension = std::filesystem::path(requestPath_).extension();
            if (const auto mimeIt = MimeTypes.find(extension); mimeIt != MimeTypes.end()) {
                const auto [ext, typePair] = *mimeIt;
                const auto [mimeType, isText] = typePair;
                if (isText) {
                    // If markdown - we'll use maddy parser
                    if (ext == ".md") {
                        if (std::ifstream ifs(requestPath_); ifs) {
                           std::shared_ptr<maddy::ParserConfig> config = std::make_shared<maddy::ParserConfig>();
                           config->isEmphasizedParserEnabled           = true; // default
                           config->isHTMLWrappedInParagraph            = true; // default

                           std::shared_ptr<maddy::Parser> parser     = std::make_shared<maddy::Parser>(config);
                           std::string                    htmlOutput = parser->Parse(ifs);
                           
                           return std::make_pair(buildHeader(htmlOutput.length(), "text/html"), htmlOutput);
                        }
                        else {
                           std::string errorStr{"Cannot read: "};
                           errorStr += requestPath_;

                           return buildErrorRespnose(404, "Not found", errorStr);
                        }
                    }
                    else if (std::ifstream ifs(requestPath_); ifs) {
                        std::string fileContents(
                                (std::istreambuf_iterator<char>(ifs)),
                                (std::istreambuf_iterator<char>()));

                        return std::make_pair(buildHeader(fileContents.length(), mimeType), fileContents);
                    }
                    else {
                        std::string errorStr{"Cannot read: "};
                        errorStr += requestPath_;
                        
                        return buildErrorRespnose(404, "Not found", errorStr);
                    }
                }
                else {
                    if (std::ifstream ifs(requestPath_, std::ios::in|std::ios::binary); ifs) {
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
                        errorStr += requestPath_;

                        return buildErrorRespnose(500, "Read error", errorStr);
                    }
                }
            }
            else {
                std::cout << "MimeType not found, considering it to be binary" << std::endl;
            }
        }
        else {
            std::string errorStr{"File: "};
            errorStr += requestPath_;
            errorStr += " was not found";

            return buildErrorRespnose(404, "File not found", errorStr);
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
