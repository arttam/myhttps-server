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
    std::string siteRoot_;
    std::string requestType_;
    std::string requestPath_;
    std::unordered_map<std::string, std::string> headers_;
public:
    explicit Parser(const std::string& root);

    std::pair<bool, std::variant<std::string, std::vector<uint8_t>>> parse(std::pair<std::string, std::string>&& request);
};

#endif
