#include "Interface.hpp"

const std::string Interface::inputStart = ">>>";
const std::string Interface::inputEnd = "<<<";
const std::string Interface::remainPrompt = "[[[";
const std::string Interface::intermediate = "----------------------------------------------------------------";
const std::string Interface::quitCommand = "QUIT";

Interface::Interface(std::istream *inputStream, std::ostream *outputStream) :
        inputStream(inputStream), outputStream(outputStream) {}

const std::string &Interface::addCommand(
        const std::string &commandType,
        const std::function<void(std::istream &, std::ostream &, Interface *)> &action) {

    return commandSet.insert({commandType, action}).first->first;
}

bool Interface::runCommand(const std::string &commandType, std::istream &commandArg) {

    try {
        if (commandType == quitCommand) {

            *outputStream << "EXIT:" << std::endl << "COMMAND TERMINAL" << std::endl;
            return true;

        } else if (commandSet.count(commandType) > 0) {

            commandSet.find(commandType)->second(commandArg, *outputStream, this);
            return false;

        } else {

            *outputStream << "EXCEPT:" << std::endl << "UNDEFINED COMMAND" << std::endl;
            return false;
        }
    } catch (std::exception &e) {

        *outputStream << "EXCEPT:" << std::endl << "[" << typeid(e).name() << "] (" << e.what() << ")" << std::endl;
        return false;

    } catch (const char *s) {

        *outputStream << "EXCEPT:" << std::endl << "\"" << s << "\"" << std::endl;
        return false;

    } catch (int i) {

        *outputStream << "EXCEPT:" << std::endl << "#" << i << std::endl;
        return false;

    } catch (...) {

        *outputStream << "EXCEPT:" << std::endl << "UNDEFINED ERROR" << std::endl;
        return false;
    }
}

int Interface::runUntilQuit() {

    *outputStream << intermediate << std::endl;

    bool isQuit = false;
    int commandCount = 0;

    while (!isQuit) {

        commandCount++;
        isQuit = runNextCommand();
    }

    return commandCount;
}

bool Interface::runNextCommand() {

    *outputStream << "command" << inputStart;
    std::string asString;
    std::getline(*inputStream, asString);
    *outputStream << asString << inputEnd << std::endl << std::endl;

    std::stringstream command(asString);
    std::string commandType;
    command >> commandType;
    bool isQuit = runCommand(commandType, command);

    bool remaining = true;
    *outputStream << std::endl << "remainder" << remainPrompt;
    while (remaining) {
        long long startAvail = command.rdbuf()->in_avail();
        std::string next;
        command >> next;
        long long endAvail = command.rdbuf()->in_avail();
        if (!next.empty()) *outputStream << next << " ";
        remaining = endAvail != 0 && endAvail != startAvail;
    }
    *outputStream << std::endl << intermediate << std::endl;

    return isQuit;
}
