#include "Token.h"

namespace Token {
    std::map<std::string, TokenType> keywords = {
        { "fn", FUNCTION },
        { "let", LET },
    };

    TokenType lookup_ident(const std::string& ident) {
        TokenType token_type = IDENT;
        if (keywords.count(ident)) {
            token_type = keywords[ident];
        }

        return token_type;
    }
}
