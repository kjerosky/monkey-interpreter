#ifndef AST_H
#define AST_H

#include <string>
#include <vector>

#include "token.h"

namespace ast {
    struct Node {
        virtual ~Node() {}

        virtual std::string get_token_literal() = 0;
        virtual std::string get_string() = 0;
    };

    struct Statement : public Node {
        virtual ~Statement() {}
    };

    struct Expression : public Node {
        virtual ~Expression() {}
    };

    struct Program : public Node {
        std::vector<Statement*> statements;

        virtual ~Program() {
            for (Statement* statement : statements) {
                delete statement;
            }
        }

        virtual std::string get_token_literal() override {
            if (statements.empty()) {
                return "";
            } else {
                return statements[0]->get_token_literal();
            }
        }

        virtual std::string get_string() override {
            std::string output;

            for (int i = 0; i < statements.size(); i++) {
                output += statements[i]->get_string();
                if (i < statements.size() - 1) {
                    output += " ";
                }
            }

            return output;
        }
    };

    struct Identifier : public Expression {
        token::Token token;
        std::string value;

        virtual std::string get_token_literal() override {
            return token.literal;
        }

        virtual std::string get_string() override {
            return value;
        }
    };

    struct LetStatement : public Statement {
        token::Token token;
        Identifier* name;
        Expression* value;

        LetStatement() {
            name = nullptr;
            value = nullptr;
        }

        virtual ~LetStatement() {
            if (name != nullptr) {
                delete name;
            }

            if (value != nullptr) {
                delete value;
            }
        }

        virtual std::string get_token_literal() override {
            return token.literal;
        }

        virtual std::string get_string() override {
            std::string output = get_token_literal() + " " + name->get_string() + " = ";

            if (value != nullptr) {
                output += value->get_string();
            }

            output += ";";

            return output;
        }
    };

    struct ReturnStatement : public Statement {
        token::Token token;
        Expression* return_value;

        ReturnStatement() {
            return_value = nullptr;
        }

        virtual ~ReturnStatement() {
            if (return_value != nullptr) {
                delete return_value;
            }
        }

        virtual std::string get_token_literal() override {
            return token.literal;
        }

        virtual std::string get_string() override {
            std::string output = get_token_literal() + " ";

            if (return_value != nullptr) {
                output += return_value->get_string();
            }

            output += ";";

            return output;
        }
    };

    struct ExpressionStatement : public Statement {
        token::Token token;
        Expression* expression;

        ExpressionStatement() {
            expression = nullptr;
        }

        virtual ~ExpressionStatement() {
            if (expression != nullptr) {
                delete expression;
            }
        }

        virtual std::string get_token_literal() override {
            return token.literal;
        }

        virtual std::string get_string() override {
            if (expression != nullptr) {
                return expression->get_string();
            }

            return "";
        }
    };
};

#endif
