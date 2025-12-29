#include <cstddef>
#include <iomanip>
#include <ios>
#include <iostream>
#include <string_view>

namespace {
    void showTitle(std::string_view programVersion)
    {
        std::cout << "\nTaskMaster " << programVersion << "\n\n";
    }

    void showCommandHelp(std::string_view command, std::string_view description,
                         size_t maxCommandLength = 20)
    {
        std::cout << '\t' << std::left << std::setw(maxCommandLength) << command << '\t'
                  << description << '\n';
    }

    void showHelp()
    {
        std::cout << "Commands:\n";
        showCommandHelp("quit", "Exit program");
        showCommandHelp("help", "Show this help");
        std::cout << '\n';
    }

    void showPrompt()
    {
        std::cout << "> ";
    }
} // namespace

int main()
{
    showTitle("v0.1.0");
    showHelp();

    bool quit {false};

    do {
        std::string command;

        showPrompt();
        std::cin >> command;

        if (command == "quit") {
            quit = true;
        } else if (command == "help") {
            showHelp();
        } else {
            std::cout << "Unknown command: '" << command << "'\n\n";
        }

    } while (quit == false);

    std::cout << "Good bye!\n\n";

    return 0;
}
