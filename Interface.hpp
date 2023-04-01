#pragma once
#include <functional>
#include <map>
#include <sstream>

// console command interface
class Interface {

private:

    // io streams
    std::istream *inputStream;
    std::ostream *outputStream;

    // all interface commands
    std::map<std::string, std::function<void(std::istream &, std::ostream &, Interface *)>> commandSet;

public:

    // user prompt
    static const std::string inputStart;
    static const std::string inputEnd;
    static const std::string remainPrompt;
    static const std::string intermediate;

    // string command to quit interface
    static const std::string quitCommand;

    // constructor

    explicit Interface(std::istream *inputStream, std::ostream *outputStream);

    virtual ~Interface() = default;

    // command operations

    const std::string &addCommand(
            const std::string &commandType,
            const std::function<void(std::istream &, std::ostream &, Interface *)> &action);

    bool runCommand(const std::string &commandType, std::istream &commandArg);

    // run interface

    int runUntilQuit();

    bool runNextCommand();
};
