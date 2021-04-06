#include "parser.h"
#include <cstring>
#include <fstream>

Parser::Parser(const std::string& root)
    : siteRoot_(root)
{

}

std::pair<bool, std::string> Parser::parse(std::pair<std::string,std::string>&& request)
{
    bool parseResult{false};
    // First line - request type
    const char *spacePtr = strchr(request.first.c_str(), ' ');
    requestType_ = std::string(request.first.c_str(), spacePtr);

    spacePtr = strchr(++spacePtr, ' ');
    requestPath_ = std::string(request.first.c_str() + requestType_.length() + 1, spacePtr);

    std::string response;
    response.append("Request type: ").append(requestType_).append("\r\n");
    response.append("Request path: ").append(requestPath_).append("\r\n");

    if (requestType_ == "GET") {
        requestPath_.insert(0, std::filesystem::current_path());
        if (std::filesystem::exists(requestPath_) && std::filesystem::is_regular_file(requestPath_)) {
            std::ifstream ifs(requestPath_);
            if (ifs) {
                std::string fileContents(
                        (std::istreambuf_iterator<char>(ifs)),
                        (std::istreambuf_iterator<char>()));

                response.append("\r\n").append(fileContents);
                parseResult = true;
            }
            else {
                response.append("\r\nCannot read").append(requestPath_);
            }
        }
        else {
            response.append("\r\nFile: ").append(requestPath_).append(" was not found");
        }
    }

    return std::make_pair(parseResult, response);
}
