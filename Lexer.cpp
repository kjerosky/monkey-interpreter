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

    position = 0;
    read_position = 0;
    read_char();
}

// --------------------------------------------------------------------------

Token::Token Lexer::next_token() {
    Token::Token token;

    skip_whitespace();

    std::string current_char_as_string(1, current_char);
    switch (current_char) {
        case '=':
            if (peek_char() == '=') {
                char previous_char = current_char;
                read_char();
                token = { Token::EQ, std::string(1, previous_char) + std::string(1, current_char) };
            } else {
                token = { Token::ASSIGN, current_char_as_string };
            }
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
        case '-':
            token = { Token::MINUS, current_char_as_string };
            break;
        case '!':
            if (peek_char() == '=') {
                char previous_char = current_char;
                read_char();
                token = { Token::NOT_EQ, std::string(1, previous_char) + std::string(1, current_char) };
            } else {
                token = {Token::BANG, current_char_as_string};
            }
            break;
        case '/':
            token = { Token::SLASH, current_char_as_string };
            break;
        case '*':
            token = { Token::ASTERISK, current_char_as_string };
            break;
        case '<':
            token = { Token::LT, current_char_as_string };
            break;
        case '>':
            token = { Token::GT, current_char_as_string };
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
        default:
            if (is_letter(current_char)) {
                token.literal = read_identifier();
                token.type = Token::lookup_ident(token.literal);

                // exit early here so we don't incorrectly read an extra character
                return token; 
            } else if (is_digit(current_char)) {
                token.type = Token::INT;
                token.literal = read_number();

                // exit early here so we don't incorrectly read an extra character
                return token; 
            } else {
                token = { Token::ILLEGAL, current_char_as_string };
            }
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

// --------------------------------------------------------------------------

std::string Lexer::read_identifier() {
    std::string identifier = "";
    while (is_letter(current_char)) {
        identifier += current_char;
        read_char();
    }

    return identifier;
}

// --------------------------------------------------------------------------

bool Lexer::is_letter(char the_char) {
    return ('a' <= the_char && the_char <= 'z') || ('A' <= the_char && the_char <= 'Z') || the_char == '_';
}

// --------------------------------------------------------------------------

void Lexer::skip_whitespace() {
    while (current_char == ' ' || current_char == '\t' || current_char == '\n' || current_char == '\r') {
        read_char();
    }
}

// --------------------------------------------------------------------------

std::string Lexer::read_number() {
    std::string number = "";
    while (is_digit(current_char)) {
        number += current_char;
        read_char();
    }

    return number;
}

// --------------------------------------------------------------------------

bool Lexer::is_digit(char the_char) {
    return '0' <= the_char && the_char <= '9';
}

// --------------------------------------------------------------------------

char Lexer::peek_char() {
    if (position >= input.length()) {
        return static_cast<char>(0);
    } else {
        return input[read_position];
    }
}
