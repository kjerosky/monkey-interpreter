#include "Parser.h"

// --------------------------------------------------------------------------

Parser::Parser(Lexer* lexer)
:
lexer(lexer) {

    // Make sure the current and peek tokens are both set.
    next_token();
    next_token();
}

// --------------------------------------------------------------------------

Parser::~Parser() {
    // nothing to do for now
}

// --------------------------------------------------------------------------

void Parser::next_token() {
    current_token = peek_token;
    peek_token = lexer->next_token();
}

// --------------------------------------------------------------------------

ast::Program* Parser::parse_program() {
    errors.clear();

    ast::Program* program = new ast::Program();

    while (current_token.type != Token::END_OF_FILE) {
        ast::Statement* statement = parse_statement();
        if (statement != nullptr) {
            program->statements.push_back(statement);
        }

        next_token();
    }

    return program;
}

// --------------------------------------------------------------------------

ast::Statement* Parser::parse_statement() {
    if (current_token.type == Token::LET) {
        return parse_let_statement();
    } else {
        return nullptr;
    }
}

// --------------------------------------------------------------------------

ast::LetStatement* Parser::parse_let_statement() {
    ast::LetStatement* let_statement = new ast::LetStatement();
    let_statement->token = current_token;

    if (!expect_peek_type(Token::IDENT)) {
        delete let_statement;
        return nullptr;
    }

    let_statement->name = new ast::Identifier();
    let_statement->name->token = current_token;
    let_statement->name->value = current_token.literal;

    if (!expect_peek_type(Token::ASSIGN)) {
        delete let_statement;
        return nullptr;
    }

    //TODO: For now, don't worry about the expression after the assignment operator.
    while (!is_current_token_type(Token::SEMICOLON)) {
        next_token();
    }

    return let_statement;
}

// --------------------------------------------------------------------------

bool Parser::is_current_token_type(Token::TokenType type) {
    return current_token.type == type;
}

// --------------------------------------------------------------------------

bool Parser::is_peek_token_type(Token::TokenType type) {
    return peek_token.type == type;
}

// --------------------------------------------------------------------------

bool Parser::expect_peek_type(Token::TokenType type) {
    if (is_peek_token_type(type)) {
        next_token();
        return true;
    } else {
        log_peek_error(type);
        return false;
    }
}

// --------------------------------------------------------------------------

std::vector<std::string>& Parser::get_errors() {
    return errors;
}

// --------------------------------------------------------------------------

void Parser::log_peek_error(Token::TokenType type) {
    std::string error_message = "unexpected next token - expected=" + type + ", actual=" + peek_token.type;
    errors.push_back(error_message);
}
