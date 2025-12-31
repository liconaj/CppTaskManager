#ifndef COMMAND_PARSER_H
#define COMMAND_PARSER_H

#include "command.h"
#include <optional>
#include <string_view>

namespace taskmaster {
std::optional<Command> parseCommand(std::string_view input);

class CommandParser
{
public:
    CommandParser() = default;
    static std::optional<Command> parse(std::string_view input);
};
}

#endif // COMMAND_PARSER_H
