#include <iostream>
#include <string>
#include <vector>

#include "ast.h"
#include "Lexer.h"
#include "Parser.h"

struct TestResult {
    bool passed;
    std::string failure_message;
};

// --------------------------------------------------------------------------

TestResult verify_let_statement(ast::Statement* statement, std::string& expected_name, int statement_number) {
    if (statement->get_token_literal() != "let") {
        return { false, "unexpected value for token literal of statement " + std::to_string(statement_number) + " - expected=let, actual=" + statement->get_token_literal() };
    }

    ast::LetStatement* let_statement = dynamic_cast<ast::LetStatement*>(statement);
    if (let_statement->name->value != expected_name) {
        return { false, "unexpected value of name of let statement " + std::to_string(statement_number) + " - expected=" + expected_name + ", actual=" + let_statement->name->value };
    } else if (let_statement->name->get_token_literal() != expected_name) {
        return { false, "unexpected token literal of name of let statement " + std::to_string(statement_number) + " - expected=" + expected_name + ", actual=" + let_statement->name->get_token_literal() };
    }

    return { true, "" };
}

// --------------------------------------------------------------------------

TestResult check_parser_for_errors(Parser& parser) {
    std::vector<std::string>& errors = parser.get_errors();
    if (errors.empty()) {
        return { true, "" };
    }

    std::string error_message = "parser had " + std::to_string(errors.size()) + " errors:";
    for (std::string error : errors) {
        error_message += "\nparser error: " + error;
    }

    return { false, error_message };
}

// --------------------------------------------------------------------------

TestResult test_let_statements() {
    std::string input = "\
let x = 5; \
let y = 10; \
let foobar = 838383; \
";

    std::vector<std::string> expected_identifiers_for_statements;
    expected_identifiers_for_statements.push_back("x");
    expected_identifiers_for_statements.push_back("y");
    expected_identifiers_for_statements.push_back("foobar");

    Lexer lexer;
    lexer.init(input);

    Parser parser(&lexer);

    ast::Program* program = parser.parse_program();
    TestResult parser_errors = check_parser_for_errors(parser);
    if (!parser_errors.passed) {
        if (program != nullptr) {
            delete program;
        }

        return { false, parser_errors.failure_message };
    }

    if (program == nullptr) {
        return { false, "parse_program() returned null" };
    } else if (program->statements.size() != expected_identifiers_for_statements.size()) {
        std::string statements_size = std::to_string(program->statements.size());

        delete program;
        return { false, "program->statements contains unexpected number of statements - expected=" + std::to_string(expected_identifiers_for_statements.size()) + ", actual=" + statements_size };
    }

    for (int i = 0; i < program->statements.size(); i++) {
        TestResult verification_result = verify_let_statement(program->statements[i], expected_identifiers_for_statements[i], i + 1);
        if (!verification_result.passed) {
            delete program;
            return verification_result;
        }
    }

    delete program;
    return { true, "" };
}

// --------------------------------------------------------------------------

TestResult test_return_statements() {
    std::string input = "\
return 5; \
return 10; \
return 993322; \
";

    int expected_statements_size = 3;
    std::string expected_token_literal = "return";

    Lexer lexer;
    lexer.init(input);

    Parser parser(&lexer);

    ast::Program* program = parser.parse_program();
    TestResult parser_errors = check_parser_for_errors(parser);
    if (!parser_errors.passed) {
        if (program != nullptr) {
            delete program;
        }

        return { false, parser_errors.failure_message };
    }

    if (program == nullptr) {
        return { false, "parse_program() returned null" };
    } else if (program->statements.size() != expected_statements_size) {
        std::string statements_size = std::to_string(program->statements.size());

        delete program;
        return { false, "program->statements contains unexpected number of statements - expected=" + std::to_string(expected_statements_size) + ", actual=" + statements_size };
    }

    for (ast::Statement* statement : program->statements) {
        if (statement->get_token_literal() != "return") {
            delete program;
            return { false, "unexpected token literal - expected=return, actual=" + statement->get_token_literal() };
        }
    }

    return { true, "" };
}

// --------------------------------------------------------------------------

int main(int argc, char** argv) {
    int failed_tests = 0;

    TestResult test_result = test_let_statements();
    if (test_result.passed) {
        std::cout << "✅ Test 1 - test_let_statements - passed" << std::endl;
    } else {
        std::cout << "❌ Test 1 - test_let_statements - failed : " << test_result.failure_message << std::endl;
        failed_tests++;
    }

    test_result = test_return_statements();
    if (test_result.passed) {
        std::cout << "✅ Test 2 - test_return_statements - passed" << std::endl;
    } else {
        std::cout << "❌ Test 2 - test_return_statements - failed : " << test_result.failure_message << std::endl;
        failed_tests++;
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
