#include "token.h"

namespace token {
    std::map<std::string, TokenType> keywords = {
        { "fn", FUNCTION },
        { "let", LET },
        { "true", TRUE },
        { "false", FALSE },
        { "if", IF },
        { "else", ELSE },
        { "return", RETURN },
    };

    TokenType lookup_ident(const std::string& ident) {
        TokenType token_type = IDENT;
        if (keywords.count(ident)) {
            token_type = keywords[ident];
        }

        return token_type;
    }
}
