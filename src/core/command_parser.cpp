#include "command_parser.h"
#include "command.h"
#include "parse_error.h"

#include <algorithm>
#include <cassert>
#include <cctype>
#include <optional>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>

namespace taskmaster {

namespace {
std::vector<std::string> tokenize(std::string_view input)
{
    std::vector<std::string> tokens;
    std::istringstream iss {std::string {input}};

    std::string token;
    while (iss >> token) {
        tokens.push_back(token);
    }

    return tokens;
}

bool hasFlag(const std::vector<std::string>& tokens, std::string_view flag)
{
    for (auto& token : tokens) {
        if (token == flag) {
            return true;
        }
    }
    return false;
}

std::string joinFrom(const std::vector<std::string>& tokens, std::size_t startIndex)
{
    if (startIndex >= tokens.size()) {
        return {};
    }

    std::string result {tokens[startIndex]};
    for (std::size_t i {startIndex + 1}; i < tokens.size(); ++i) {
        result += ' ';
        result += tokens[i];
    }

    return result;
}

std::string toLower(std::string str)
{
    std::transform(str.begin(), str.end(), str.begin(),
                   [](unsigned char c) { return static_cast<char>(std::tolower(c)); });
    return str;
}
} // namespace

std::optional<Command> parseCommand(std::string_view input)
{
    std::vector<std::string> tokens {tokenize(input)};

    if (tokens.empty() == true) {
        return std::nullopt;
    }

    auto cmd = toLower(tokens[0]);

    if (cmd == "quit" || cmd == "exit") {
        return QuitCommand {};
    }

    if (cmd == "add") {
        if (tokens.size() < 2) {
            throw MissingArgumentError {"add", "description"};
        }
        const std::string description {joinFrom(tokens, 1)};
        return AddCommand {description};
    }

    if (cmd == "list") {
        return ListCommand {hasFlag(tokens, "-a") || hasFlag(tokens, "--all")};
    }

    if (cmd == "help") {
        return HelpCommand {};
    }

    throw UnknownCommandError {cmd};
}

} // namespace taskmaster
