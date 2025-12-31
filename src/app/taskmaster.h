#ifndef TASKMASTER_H
#define TASKMASTER_H

#include "command.h"

namespace taskmaster {

class TaskMaster
{
public:
    TaskMaster() = default;
    void run();

private:
    static constexpr std::string_view VERSION = "0.1.0";
    bool m_running {true};

    void handle(const AddCommand& cmd);
    void handle(const QuitCommand& cmd);
    void handle(const ListCommand& cmd);
    void handle(const HelpCommand& cmd);
};

} // namespace taskmaster

#endif // TASKMASTER_H
