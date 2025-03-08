CC = g++
FLAGS = -Wall --std=c++17

TEST_LEXER_EXECUTABLE = test_lexer
TEST_LEXER_SOURCES = lexer_test.cpp lexer.cpp

$(TEST_LEXER_EXECUTABLE) : $(TEST_LEXER_SOURCES)
	$(CC) $(FLAGS) -o $@ $^

clean:
	rm -rf $(TEST_LEXER_EXECUTABLE)
