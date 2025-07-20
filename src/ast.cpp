#include "ast.h"

namespace ast {

    Node::~Node() {
        // nothing to do for now
    }

    // ----------------------------------------------------------------------

    Statement::~Statement() {
        // nothing to do for now
    }

    // ----------------------------------------------------------------------

    Expression::~Expression() {
        // nothing to do for now
    }

    // ----------------------------------------------------------------------

    Program::~Program() {
        for (Statement* statement : statements) {
            delete statement;
        }
    }

    std::string Program::get_token_literal() {
        if (statements.empty()) {
            return "";
        } else {
            return statements[0]->get_token_literal();
        }
    }

    std::string Program::get_string() {
        std::string output;

        for (int i = 0; i < statements.size(); i++) {
            output += statements[i]->get_string();
            if (i < statements.size() - 1) {
                output += " ";
            }
        }

        return output;
    }

    // ----------------------------------------------------------------------

    std::string Identifier::get_token_literal() {
        return token.literal;
    }

    std::string Identifier::get_string() {
        return value;
    }

    // ----------------------------------------------------------------------

    LetStatement::LetStatement() {
        name = nullptr;
        value = nullptr;
    }

    LetStatement::~LetStatement() {
        if (name != nullptr) {
            delete name;
        }

        if (value != nullptr) {
            delete value;
        }
    }

    std::string LetStatement::get_token_literal() {
        return token.literal;
    }

    std::string LetStatement::get_string() {
        std::string output = get_token_literal() + " " + name->get_string() + " = ";

        if (value != nullptr) {
            output += value->get_string();
        }

        output += ";";

        return output;
    }

    // ----------------------------------------------------------------------

    ReturnStatement::ReturnStatement() {
        return_value = nullptr;
    }

    ReturnStatement::~ReturnStatement() {
        if (return_value != nullptr) {
            delete return_value;
        }
    }

    std::string ReturnStatement::get_token_literal() {
        return token.literal;
    }

    std::string ReturnStatement::get_string() {
        std::string output = get_token_literal() + " ";

        if (return_value != nullptr) {
            output += return_value->get_string();
        }

        output += ";";

        return output;
    }

    // ----------------------------------------------------------------------

    ExpressionStatement::ExpressionStatement() {
        expression = nullptr;
    }

    ExpressionStatement::~ExpressionStatement() {
        if (expression != nullptr) {
            delete expression;
        }
    }

    std::string ExpressionStatement::get_token_literal() {
        return token.literal;
    }

    std::string ExpressionStatement::get_string() {
        if (expression != nullptr) {
            return expression->get_string();
        }

        return "";
    }
};
