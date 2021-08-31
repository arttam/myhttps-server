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
    using TextResponse = std::pair<std::string, std::string>;
    using ByteResponse = std::pair<std::string, std::vector<uint8_t>>;
    TextResponse buildErrorRespnose(int errorCode, const std::string& errorStr, const std::string& message) const;
    std::string buildHeader(int contentLength, const std::string& contentType=std::string{"text/html"}, int code=200, const std::string& status=std::string{"OK"}) const;

    void beautifyCode(std::string& payload) const;

    // Helpers, in order to make code neat
    TextResponse textFile(const std::filesystem::path& pTarget, const std::string& mimeType) const;
    TextResponse MDFile(const std::filesystem::path& pTarget) const;

    std::variant<ByteResponse, TextResponse> binaryFile(const std::filesystem::path& pTarget, const std::string& mimeType) const;
};

#endif
