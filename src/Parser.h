#ifndef PARSER_H
#define PARSER_H

#include <vector>
#include <string>

#include "ast.h"
#include "Lexer.h"
#include "token.h"

class Parser {

public:

    Parser(Lexer* lexer);
    ~Parser();

    ast::Program* parse_program();
    std::vector<std::string>& get_errors();

private:

    Lexer* lexer;
    token::Token current_token;
    token::Token peek_token;
    std::vector<std::string> errors;

    void next_token();
    bool is_current_token_type(token::TokenType type);
    bool is_peek_token_type(token::TokenType type);
    bool expect_peek_type(token::TokenType type);
    ast::Statement* parse_statement();
    ast::LetStatement* parse_let_statement();
    void log_peek_error(token::TokenType type);
};

#endif
