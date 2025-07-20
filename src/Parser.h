#ifndef PARSER_H
#define PARSER_H

#include <vector>
#include <string>

#include "ast.h"
#include "Lexer.h"
#include "Token.h"

class Parser {

public:

    Parser(Lexer* lexer);
    ~Parser();

    ast::Program* parse_program();
    std::vector<std::string>& get_errors();

private:

    Lexer* lexer;
    Token::Token current_token;
    Token::Token peek_token;
    std::vector<std::string> errors;

    void next_token();
    bool is_current_token_type(Token::TokenType type);
    bool is_peek_token_type(Token::TokenType type);
    bool expect_peek_type(Token::TokenType type);
    ast::Statement* parse_statement();
    ast::LetStatement* parse_let_statement();
    void log_peek_error(Token::TokenType type);
};

#endif
