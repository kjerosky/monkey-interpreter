#include "Repl.h"

#include <iostream>

#include "Token.h"

Repl::Repl() {
    // do nothing
}

// --------------------------------------------------------------------------

Repl::~Repl() {
    // do nothing
}

// --------------------------------------------------------------------------

void Repl::start() {
    std::string line;

    while (true) {
        std::cout << PROMPT;
        std::getline(std::cin, line);

        lexer.init(line);
        if (line.length() <= 0) {
            return;
        }

        for (Token::Token token = lexer.next_token(); token.type != Token::END_OF_FILE; token = lexer.next_token()) {
            std::cout << "{ type=\"" << token.type << "\", literal=\"" << token.literal << "\" }" << std::endl;
        }
        std::cout << std::endl;
    }
}
