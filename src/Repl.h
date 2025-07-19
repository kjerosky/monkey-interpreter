#ifndef REPL_H
#define REPL_H

#include <string>

#include "Lexer.h"

class Repl {

public:

    Repl();
    ~Repl();

    void start();

private:

    const std::string PROMPT = ">> ";

    Lexer lexer;
};

#endif
