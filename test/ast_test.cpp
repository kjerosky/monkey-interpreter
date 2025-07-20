#include <iostream>
#include <string>

#include "ast.h"

struct TestResult {
    bool passed;
    std::string failure_message;
};

// --------------------------------------------------------------------------

TestResult test_string() {
    std::string expected_program_string = "let myVar = anotherVar;";
    ast::Program* program = new ast::Program();

    ast::Identifier* lhs_identifier = new ast::Identifier();
    lhs_identifier->token = { token::IDENT, "myVar" };
    lhs_identifier->value = "myVar";

    ast::Identifier* rhs_identifier = new ast::Identifier();
    rhs_identifier->token = { token::IDENT, "anotherVar" };
    rhs_identifier->value = "anotherVar";

    ast::LetStatement* let_statement = new ast::LetStatement();
    let_statement->token = { token::LET, "let" };
    let_statement->name = lhs_identifier;
    let_statement->value = rhs_identifier;
    program->statements.push_back(let_statement);

    std::string actual_program_string = program->get_string();
    if (actual_program_string != expected_program_string) {
        delete program;
        return { false, "unexpected value for program->get_string() -\nexpected=\"" + expected_program_string + "\"\n  actual=\"" + actual_program_string + "\"" };
    }

    delete program;
    return { true, "" };
}

// --------------------------------------------------------------------------

int main(int argc, char** argv) {
    int failed_tests = 0;

    TestResult test_result = test_string();
    if (test_result.passed) {
        std::cout << "✅ Test 1 - test_string - passed" << std::endl;
    } else {
        std::cout << "❌ Test 1 - test_string - failed : " << test_result.failure_message << std::endl;
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
