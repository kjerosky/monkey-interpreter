#include <iostream>

#include "Repl.h"

int main(int argc, char** argv) {
    std::cout << "Hello and welcome to the Monkey programming language!" << std::endl;
    std::cout << "Feel free to type in commands." << std::endl;
    std::cout << "Enter the EOF character (ctrl-D) by itself or just press the enter key at a new prompt to quit." << std::endl;
    std::cout << std::endl;

    Repl repl;
    repl.start();

    return 0;
}
