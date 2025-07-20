#ifndef AST_H
#define AST_H

#include <string>
#include <vector>

#include "token.h"

namespace ast {
    struct Node {
        virtual ~Node() {}

        virtual std::string get_token_literal() = 0;
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
    };

    struct Identifier : public Expression {
        token::Token token;
        std::string value;

        virtual std::string get_token_literal() override {
            return token.literal;
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
    };
};

#endif
