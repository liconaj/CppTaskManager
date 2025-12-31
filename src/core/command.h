#ifndef COMMAND_H
#define COMMAND_H

#include <string>
#include <variant>

namespace taskmaster {

struct AddCommand
{
    std::string description;
};

struct ListCommand
{
    bool showAll {false};
};

struct QuitCommand
{
};

struct HelpCommand
{
};

using Command = std::variant<AddCommand, ListCommand, QuitCommand, HelpCommand>;

} // namespace taskmaster

#endif // COMMAND_H
