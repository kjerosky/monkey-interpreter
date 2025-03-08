#ifndef LEXER_H
#define LEXER_H

#include <string>

#include "Token.h"

class Lexer {

public:

    Lexer();
    ~Lexer();

    void init(const std::string& input);
    Token::Token next_token();

private:

    std::string input;
    int position;
    int read_position;
    char current_char;

    void read_char();
};

#endif
