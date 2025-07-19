#ifndef TOKEN_H
#define TOKEN_H

#include <string>
#include <map>

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
    const TokenType MINUS = "-";
    const TokenType BANG = "!";
    const TokenType ASTERISK = "*";
    const TokenType SLASH = "/";

    const TokenType LT = "<";
    const TokenType GT = ">";
    const TokenType EQ = "==";
    const TokenType NOT_EQ = "!=";

    const TokenType COMMA = ",";
    const TokenType SEMICOLON = ";";

    const TokenType LPAREN = "(";
    const TokenType RPAREN = ")";
    const TokenType LBRACE = "{";
    const TokenType RBRACE = "}";

    const TokenType FUNCTION = "FUNCTION";
    const TokenType LET = "LET";
    const TokenType TRUE = "TRUE";
    const TokenType FALSE = "FALSE";
    const TokenType IF = "IF";
    const TokenType ELSE = "ELSE";
    const TokenType RETURN = "RETURN";

    extern std::map<std::string, TokenType> keywords;

    TokenType lookup_ident(const std::string& ident);
}

#endif
