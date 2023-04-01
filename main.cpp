#include "SplitInterface.hpp"

int main() {

    SplitInterface interface = SplitInterface(&std::cin, &std::cout);
    interface.runUntilQuit();
}
