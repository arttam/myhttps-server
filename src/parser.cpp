#include "parser.h"
#include <cstring>
#include <fstream>

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

Parser::Parser(const std::string& root)
    : siteRoot_(root)
{

}

std::pair<bool, std::variant<std::string, std::vector<uint8_t>>> Parser::parse(std::pair<std::string, std::string>&& request)
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
                    if (std::ifstream ifs(requestPath_); ifs) {
                        std::string fileContents(
                                (std::istreambuf_iterator<char>(ifs)),
                                (std::istreambuf_iterator<char>()));

                        return std::make_pair(true, fileContents);
                    }
                    else {
                        std::string errorStr{"Cannot read: "};
                        errorStr += requestPath_;
                        
                        return std::make_pair(false, errorStr);
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
                            return std::make_pair(true, buffer);
                        }
                        else {
                            std::string errorStr{"Failed to read data into buffer"};
                            return std::make_pair(false, errorStr);
                        }
                    }
                    else {
                        std::string errorStr{"Cannot read: "};
                        errorStr += requestPath_;

                        return std::make_pair(parseResult, errorStr);
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
            return std::make_pair(parseResult, errorStr);
        }
    }

    return std::make_pair(parseResult, std::vector<uint8_t>{});
}
