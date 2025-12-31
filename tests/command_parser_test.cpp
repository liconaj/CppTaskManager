#include <catch2/catch_test_macros.hpp>
#include <variant>

#include "command.h"
#include "command_parser.h"
#include "parse_error.h"

namespace {

using namespace taskmaster;

template<typename T>
T getCommand(const std::string& input)
{
    std::optional<Command> result;
    REQUIRE_NOTHROW(result = parseCommand(input));
    if (result.has_value()) {
        auto& command = result.value();
        REQUIRE(std::holds_alternative<T>(command));
        return std::get<T>(command);
    } else {
        FAIL("parse command returned null option");
    }
}

// --------------------------------------------------------
// `add` command

TEST_CASE("Parse add command", "[parser][add]")
{
    auto cmd = getCommand<AddCommand>("add Eat");
    REQUIRE(cmd.description == "Eat");
}

TEST_CASE("Parse add command with description with multiple words", "[parser][add]")
{
    auto cmd = getCommand<AddCommand>("add Buy milk, eggs, and cheese.");
    REQUIRE(cmd.description == "Buy milk, eggs, and cheese.");
}

TEST_CASE("Parse add without description throws", "[parser][add]")
{
    REQUIRE_THROWS_AS(parseCommand("add"), MissingArgumentError);
}

TEST_CASE("Parse add ignores inner multiple spaces", "[parser][add]")
{
    auto cmd = getCommand<AddCommand>("add Hello    world");
    REQUIRE(cmd.description == "Hello world");
}

// --------------------------------------------------------
// `quit` command

TEST_CASE("Parse quit command", "[parser][quit]")
{
    getCommand<QuitCommand>("quit");
    getCommand<QuitCommand>("exit");
}

TEST_CASE("Parse quit with arguments do not throw error", "[parser][quit]")
{
    getCommand<QuitCommand>("quit foo");
}

// --------------------------------------------------------
// `list` command

TEST_CASE("Parse list command", "[parser][list]")
{
    auto cmd = getCommand<ListCommand>("list");
    REQUIRE_FALSE(cmd.showAll);
}

TEST_CASE("Parse list command with --all flag makes showAll true", "[parser][list]")
{
    auto cmd = getCommand<ListCommand>("list --all");
    REQUIRE(cmd.showAll);
}

TEST_CASE("Parse list command with shorthand -a flag makes showAll true", "[parser][list]")
{
    auto cmd = getCommand<ListCommand>("list -a");
    REQUIRE(cmd.showAll);
}

// --------------------------------------------------------
// `help` command
TEST_CASE("Parse help command", "[parser][help]")
{
    getCommand<HelpCommand>("help");
}

TEST_CASE("Parse help with arguments do not throw error", "[parser][help]")
{
    getCommand<HelpCommand>("help foo");
}

// --------------------------------------------------------
// Command case

TEST_CASE("Parse command is case insensitive", "[parser]")
{
    auto cmd = getCommand<AddCommand>("ADd something");
    REQUIRE(cmd.description == "something");
}

// --------------------------------------------------------
// Unknown command

TEST_CASE("Parse unknown command throws", "[parser]")
{
    REQUIRE_THROWS_AS(parseCommand("foo"), UnknownCommandError);
}

TEST_CASE("Parse unknown command with arguments throws", "[parser]")
{
    REQUIRE_THROWS_AS(parseCommand("foo bar"), UnknownCommandError);
}

// --------------------------------------------------------
// Whitespace handling

TEST_CASE("Parse trims leading and trailing spaces", "[parser]")
{
    auto cmd = getCommand<AddCommand>(" add    Wash dishes ");
    REQUIRE(cmd.description == "Wash dishes");
}

TEST_CASE("Parse whitespace only returns nullopt", "[parser]")
{
    auto result {parseCommand("    ")};
    REQUIRE_FALSE(result.has_value());
}

TEST_CASE("Parse empty input return nullopt", "[parser]")
{
    auto result {parseCommand("")};
    REQUIRE_FALSE(result.has_value());
}

} // namespace
