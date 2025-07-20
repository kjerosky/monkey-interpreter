#include <iostream>
#include <vector>

#include "Lexer.h"

int main(int argc, char** argv) {
    int failed_tests = 0;

    std::string input = "let five = 5;\
let ten = 10;\
\
let add = fn(x, y) {\
    x + y;\
};\
\
let result = add(five, ten);\
!-/*5;\
5 < 10 > 5;\
\
if (5 < 10) {\
    return true;\
} else {\
    return false;\
}\
\
10 == 10;\
10 != 9;\
";

    std::vector<token::Token> expected_tokens = {
        { token::LET, "let" },
        { token::IDENT, "five" },
        { token::ASSIGN, "=" },
        { token::INT, "5" },
        { token::SEMICOLON, ";" },
        { token::LET, "let" },
        { token::IDENT, "ten" },
        { token::ASSIGN, "=" },
        { token::INT, "10" },
        { token::SEMICOLON, ";" },
        { token::LET, "let" },
        { token::IDENT, "add" },
        { token::ASSIGN, "=" },
        { token::FUNCTION, "fn" },
        { token::LPAREN, "(" },
        { token::IDENT, "x" },
        { token::COMMA, "," },
        { token::IDENT, "y" },
        { token::RPAREN, ")" },
        { token::LBRACE, "{" },
        { token::IDENT, "x" },
        { token::PLUS, "+" },
        { token::IDENT, "y" },
        { token::SEMICOLON, ";" },
        { token::RBRACE, "}" },
        { token::SEMICOLON, ";" },
        { token::LET, "let" },
        { token::IDENT, "result" },
        { token::ASSIGN, "=" },
        { token::IDENT, "add" },
        { token::LPAREN, "(" },
        { token::IDENT, "five" },
        { token::COMMA, "," },
        { token::IDENT, "ten" },
        { token::RPAREN, ")" },
        { token::SEMICOLON, ";" },
        { token::BANG, "!" },
        { token::MINUS, "-" },
        { token::SLASH, "/" },
        { token::ASTERISK, "*" },
        { token::INT, "5" },
        { token::SEMICOLON, ";" },
        { token::INT, "5" },
        { token::LT, "<" },
        { token::INT, "10" },
        { token::GT, ">" },
        { token::INT, "5" },
        { token::SEMICOLON, ";" },
        { token::IF, "if" },
        { token::LPAREN, "(" },
        { token::INT, "5" },
        { token::LT, "<" },
        { token::INT, "10" },
        { token::RPAREN, ")" },
        { token::LBRACE, "{" },
        { token::RETURN, "return" },
        { token::TRUE, "true" },
        { token::SEMICOLON, ";" },
        { token::RBRACE, "}" },
        { token::ELSE, "else" },
        { token::LBRACE, "{" },
        { token::RETURN, "return" },
        { token::FALSE, "false" },
        { token::SEMICOLON, ";" },
        { token::RBRACE, "}" },
        { token::INT, "10" },
        { token::EQ, "==" },
        { token::INT, "10" },
        { token::SEMICOLON, ";" },
        { token::INT, "10" },
        { token::NOT_EQ, "!=" },
        { token::INT, "9" },
        { token::SEMICOLON, ";" },
        { token::END_OF_FILE, "" },
    };

    Lexer lexer;
    lexer.init(input);

    for (int i = 0; i < expected_tokens.size(); i++) {
        bool did_test_fail = false;

        token::Token token = lexer.next_token();

        token::Token expected_token = expected_tokens[i];

        if (token.type != expected_token.type) {
            std::cout << "❌ Test [" << i + 1 << "] - wrong token type : expected=\"" << expected_token.type << "\", actual=\"" << token.type << "\"" << std::endl;
            did_test_fail = true;
        }

        if (token.literal != expected_token.literal) {
            std::cout << "❌ Test [" << i + 1 << "] - wrong literal : expected=\"" << expected_token.literal << "\", actual=\"" << token.literal << "\"" << std::endl;
            did_test_fail = true;
        }

        if (did_test_fail) {
            failed_tests++;
        } else {
            std::cout << "✅ Test [" << i + 1 << "] - passed : token={ " << token.type << ", " << token.literal << " }" << std::endl;
        }
    }

    std::cout << std::endl << "RESULTS: ";
    if (failed_tests > 0) {
        std::cout << "❌ " << failed_tests << " tests failed!" << std::endl;
        return 1;
    } else {
        std::cout << "✅ All tests passed!" << std::endl;
        return 0;
    }
}
