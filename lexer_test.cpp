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

    std::vector<Token::Token> expected_tokens = {
        { Token::LET, "let" },
        { Token::IDENT, "five" },
        { Token::ASSIGN, "=" },
        { Token::INT, "5" },
        { Token::SEMICOLON, ";" },
        { Token::LET, "let" },
        { Token::IDENT, "ten" },
        { Token::ASSIGN, "=" },
        { Token::INT, "10" },
        { Token::SEMICOLON, ";" },
        { Token::LET, "let" },
        { Token::IDENT, "add" },
        { Token::ASSIGN, "=" },
        { Token::FUNCTION, "fn" },
        { Token::LPAREN, "(" },
        { Token::IDENT, "x" },
        { Token::COMMA, "," },
        { Token::IDENT, "y" },
        { Token::RPAREN, ")" },
        { Token::LBRACE, "{" },
        { Token::IDENT, "x" },
        { Token::PLUS, "+" },
        { Token::IDENT, "y" },
        { Token::SEMICOLON, ";" },
        { Token::RBRACE, "}" },
        { Token::SEMICOLON, ";" },
        { Token::LET, "let" },
        { Token::IDENT, "result" },
        { Token::ASSIGN, "=" },
        { Token::IDENT, "add" },
        { Token::LPAREN, "(" },
        { Token::IDENT, "five" },
        { Token::COMMA, "," },
        { Token::IDENT, "ten" },
        { Token::RPAREN, ")" },
        { Token::SEMICOLON, ";" },
        { Token::BANG, "!" },
        { Token::MINUS, "-" },
        { Token::SLASH, "/" },
        { Token::ASTERISK, "*" },
        { Token::INT, "5" },
        { Token::SEMICOLON, ";" },
        { Token::INT, "5" },
        { Token::LT, "<" },
        { Token::INT, "10" },
        { Token::GT, ">" },
        { Token::INT, "5" },
        { Token::SEMICOLON, ";" },
        { Token::IF, "if" },
        { Token::LPAREN, "(" },
        { Token::INT, "5" },
        { Token::LT, "<" },
        { Token::INT, "10" },
        { Token::RPAREN, ")" },
        { Token::LBRACE, "{" },
        { Token::RETURN, "return" },
        { Token::TRUE, "true" },
        { Token::SEMICOLON, ";" },
        { Token::RBRACE, "}" },
        { Token::ELSE, "else" },
        { Token::LBRACE, "{" },
        { Token::RETURN, "return" },
        { Token::FALSE, "false" },
        { Token::SEMICOLON, ";" },
        { Token::RBRACE, "}" },
        { Token::INT, "10" },
        { Token::EQ, "==" },
        { Token::INT, "10" },
        { Token::SEMICOLON, ";" },
        { Token::INT, "10" },
        { Token::NOT_EQ, "!=" },
        { Token::INT, "9" },
        { Token::SEMICOLON, ";" },
        { Token::END_OF_FILE, "" },
    };

    Lexer lexer;
    lexer.init(input);

    for (int i = 0; i < expected_tokens.size(); i++) {
        bool did_test_fail = false;

        Token::Token token = lexer.next_token();

        Token::Token expected_token = expected_tokens[i];

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
