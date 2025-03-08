#ifndef TOKEN_H
#define TOKEN_H

#include <string>

namespace Token {
    typedef std::string TokenType;

    struct Token {
        TokenType type;
        std::string literal;
    };

    const TokenType ILLEGAL = "ILLEGAL";
    const TokenType END_OF_FILE = "EOF";

    const TokenType IDENT = "IDENT";
    const TokenType INT = "INT";

    const TokenType ASSIGN = "=";
    const TokenType PLUS = "+";

    const TokenType COMMA = ",";
    const TokenType SEMICOLON = ";";

    const TokenType LPAREN = "(";
    const TokenType RPAREN = ")";
    const TokenType LBRACE = "{";
    const TokenType RBRACE = "}";

    const TokenType FUNCTION = "FUNCTION";
    const TokenType LET = "LET";
}

#endif
