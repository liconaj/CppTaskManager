#ifndef PARSE_ERROR_H
#define PARSE_ERROR_H

#include <stdexcept>
#include <string>

namespace taskmaster {

class ParseError : public std::runtime_error
{
public:
    explicit ParseError(const std::string& what) : std::runtime_error(what) { }
};

class UnknownCommandError : public ParseError
{
public:
    explicit UnknownCommandError(const std::string& command)
        : ParseError("unknown command " + command)
    {
    }
};

class MissingArgumentError : public ParseError
{
public:
    explicit MissingArgumentError(const std::string& command, const std::string& argument)
        : ParseError(command + " requires " + argument)
    {
    }
};

class InvalidArgumentError : public ParseError
{
public:
    explicit InvalidArgumentError(const std::string& command, const std::string& argument,
                                  const std::string& value)
        : ParseError(command + ": invalid " + argument + " '" + value + "'")
    {
    }
};

} // namespace taskmaster

#endif // PARSE_ERROR_H
