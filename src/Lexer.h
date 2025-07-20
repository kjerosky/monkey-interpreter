#ifndef LEXER_H
#define LEXER_H

#include <string>

#include "token.h"

class Lexer {

public:

    Lexer();
    ~Lexer();

    void init(const std::string& input);
    token::Token next_token();

private:

    std::string input;
    int position;
    int read_position;
    char current_char;

    void read_char();
    std::string read_identifier();
    bool is_letter(char the_char);
    void skip_whitespace();
    std::string read_number();
    bool is_digit(char the_char);
    char peek_char();
};

#endif
