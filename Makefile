CC = g++
FLAGS = -g -Wall --std=c++17

INTERPRETER_EXECUTABLE = monkey-interpreter
INTERPRETER_SOURCES = main.cpp Repl.cpp Lexer.cpp Token.cpp

TEST_LEXER_EXECUTABLE = test_lexer
TEST_LEXER_SOURCES = lexer_test.cpp Lexer.cpp Token.cpp

$(INTERPRETER_EXECUTABLE) : $(INTERPRETER_SOURCES)
	$(CC) $(FLAGS) -o $@ $^

$(TEST_LEXER_EXECUTABLE) : $(TEST_LEXER_SOURCES)
	$(CC) $(FLAGS) -o $@ $^

clean:
	rm -rf *.dSYM $(INTERPRETER_EXECUTABLE) $(TEST_LEXER_EXECUTABLE)
