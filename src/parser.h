#ifndef __USES_PARSER_H__
#define __USES_PARSER_H__

#include <filesystem>
#include <string>
#include <utility>
#include <unordered_map>

class Parser
{
    std::string siteRoot_;
    std::string requestType_;
    std::string requestPath_;
    std::unordered_map<std::string, std::string> headers_;
public:
    explicit Parser(const std::string& root);

    std::pair<bool, std::string> parse(std::pair<std::string, std::string>&& request);
};

#endif
