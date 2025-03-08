#include "Lexer.h"

Lexer::Lexer() {
    // do nothing
}

// --------------------------------------------------------------------------

Lexer::~Lexer() {
    // do nothing
}

// --------------------------------------------------------------------------

void Lexer::init(const std::string& input) {
    this->input = input;
    read_char();
}

// --------------------------------------------------------------------------

Token::Token Lexer::next_token() {
    Token::Token token;

    std::string current_char_as_string(1, current_char);
    switch (current_char) {
        case '=':
            token = { Token::ASSIGN, current_char_as_string };
            break;
        case ';':
            token = { Token::SEMICOLON, current_char_as_string };
            break;
        case '(':
            token = { Token::LPAREN, current_char_as_string };
            break;
        case ')':
            token = { Token::RPAREN, current_char_as_string };
            break;
        case ',':
            token = { Token::COMMA, current_char_as_string };
            break;
        case '+':
            token = { Token::PLUS, current_char_as_string };
            break;
        case '{':
            token = { Token::LBRACE, current_char_as_string };
            break;
        case '}':
            token = { Token::RBRACE, current_char_as_string };
            break;
        case static_cast<char>(0):
            token = { Token::END_OF_FILE, "" };
            break;
    }

    read_char();

    return token;
}

// --------------------------------------------------------------------------

void Lexer::read_char() {
    if (read_position >= input.length()) {
        current_char = static_cast<char>(0);
    } else {
        current_char = input[read_position];
    }

    position = read_position;
    read_position++;
}
