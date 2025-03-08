CC = g++
FLAGS = -g -Wall --std=c++17

TEST_LEXER_EXECUTABLE = test_lexer
TEST_LEXER_SOURCES = lexer_test.cpp Lexer.cpp Token.cpp

$(TEST_LEXER_EXECUTABLE) : $(TEST_LEXER_SOURCES)
	$(CC) $(FLAGS) -o $@ $^

clean:
	rm -rf $(TEST_LEXER_EXECUTABLE)
