.PHONY: all test

CC = gcc

OUT = build/str
TEST_OUT = build/str_test

SRC = src/main.c src/str.c
TEST_SRC = test/str_tests.c src/str.c

all:
	mkdir -p build
	$(CC) $(SRC) -o $(OUT)

test:
	mkdir -p build
	$(CC) $(TEST_SRC) -o $(TEST_OUT)
	./$(TEST_OUT)