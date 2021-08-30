#ifndef __USES_PARSER_H__
#define __USES_PARSER_H__

#include <filesystem>
#include <string>
#include <vector>
#include <utility>
#include <unordered_map>
#include <variant>

class Parser
{
    std::string docRoot_;
    std::string requestType_;
    std::string requestPath_;
    std::unordered_map<std::string, std::string> headers_;

public:
    explicit Parser(const std::string& docRoot);

    std::pair<std::string, std::variant<std::string, std::vector<uint8_t>>> parse(std::pair<std::string, std::string>&& request);

private:
    // pair: header, body
    std::pair<std::string, std::string> buildErrorRespnose(int errorCode, const std::string& errorStr, const std::string& message) const;
    std::string buildHeader(int contentLength, const std::string& contentType=std::string{"text/html"}, int code=200, const std::string& status=std::string{"OK"}) const;
};

#endif
