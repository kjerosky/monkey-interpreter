#ifndef AST_H
#define AST_H

#include <string>
#include <vector>

#include "token.h"

namespace ast {

    struct Node {
        virtual ~Node();

        virtual std::string get_token_literal() = 0;
        virtual std::string get_string() = 0;
    };

    // ----------------------------------------------------------------------

    struct Statement : public Node {
        virtual ~Statement();
    };

    // ----------------------------------------------------------------------

    struct Expression : public Node {
        virtual ~Expression();
    };

    // ----------------------------------------------------------------------

    struct Program : public Node {
        std::vector<Statement*> statements;

        virtual ~Program();

        virtual std::string get_token_literal() override;
        virtual std::string get_string() override;
    };

    // ----------------------------------------------------------------------

    struct Identifier : public Expression {
        token::Token token;
        std::string value;

        virtual std::string get_token_literal() override;
        virtual std::string get_string() override;
    };

    // ----------------------------------------------------------------------

    struct LetStatement : public Statement {
        token::Token token;
        Identifier* name;
        Expression* value;

        LetStatement();
        virtual ~LetStatement();

        virtual std::string get_token_literal() override;
        virtual std::string get_string() override;
    };

    // ----------------------------------------------------------------------

    struct ReturnStatement : public Statement {
        token::Token token;
        Expression* return_value;

        ReturnStatement();
        virtual ~ReturnStatement();

        virtual std::string get_token_literal() override;
        virtual std::string get_string() override;
    };

    // ----------------------------------------------------------------------

    struct ExpressionStatement : public Statement {
        token::Token token;
        Expression* expression;

        ExpressionStatement();
        virtual ~ExpressionStatement();

        virtual std::string get_token_literal() override;
        virtual std::string get_string() override;
    };
};

#endif
