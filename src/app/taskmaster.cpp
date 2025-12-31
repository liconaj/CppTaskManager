#include <iomanip>
#include <iostream>
#include <optional>
#include <string>
#include <variant>

#include "command.h"
#include "command_parser.h"
#include "parse_error.h"
#include "taskmaster.h"

namespace taskmaster {

namespace {
void showTitle(std::string_view programVersion)
{
    std::cout << "\nTaskMaster " << programVersion << "\n\n";
}

void showCommandHelp(std::string_view command, std::string_view description,
                     size_t maxCommandLength = 20)
{
    std::cout << std::string(4, ' ') << std::left << std::setw(maxCommandLength) << command << '\t'
              << description << '\n';
}

void showHelp()
{
    std::cout << "Commands:\n";
    showCommandHelp("quit or exit", "Exit program");
    showCommandHelp("help", "Show this help");
    showCommandHelp("add <description>", "Add task");
    showCommandHelp("list [--all | -a]", "List tasks");
    std::cout << '\n';
}

void showPrompt()
{
    std::cout << "> ";
}

void showGoodbye()
{
    std::cout << "Good bye!\n\n";
}

void showWelcome()
{
    showTitle("v0.1.0");
    showHelp();
}
} // namespace

void TaskMaster::run()
{
    showWelcome();

    std::string input;

    while (m_running) {
        showPrompt();
        std::getline(std::cin, input);

        try {
            std::optional<Command> cmd = parseCommand(input);
            if (cmd.has_value() == false) {
                continue;
            }
            std::visit([this](const auto& c) { handle(c); }, cmd.value());
        } catch (const ParseError& e) {
            std::cout << "Error: " << e.what() << "\n\n";
        }
    }

    showGoodbye();
}

void TaskMaster::handle(const QuitCommand&)
{
    m_running = false;
}

void TaskMaster::handle(const AddCommand& cmd)
{
    std::cout << "Adding task '" << cmd.description << "'..." << "\n\n";
}

void TaskMaster::handle(const ListCommand& cmd)
{
    if (cmd.showAll) {
        std::cout << "Listing all tasks..." << "\n\n";
    } else {
        std::cout << "Listing tasks..." << "\n\n";
    }
}

void TaskMaster::handle(const HelpCommand&)
{
    showHelp();
}

} // namespace taskmaster
