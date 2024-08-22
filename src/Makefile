CC = gcc
FLAGS = -std=c11 -Werror -Wextra -Wall

SRC=$(wildcard s21_*.c)
TEST_SRC=$(wildcard tests/*.c) unit_tests.c

OBJ=$(patsubst %.c,%.o,$(SRC))
TEST_OBJ=$(patsubst tests/%.c,%.o,$(TEST_SRC))
GCOV_TEST_OBJ=$(patsubst %, gcov_%, $(OBJ))


OS := $(shell uname -s)
ifeq ($(OS), Darwin)
    CHECK_FLAGS=-lcheck
else
	CHECK_FLAGS=-pthread -lcheck_pic -pthread -lrt -lm -lsubunit
endif


GCOV_FLAGS = --coverage

.PHONY: all clean rebuild

all: s21_string.a

s21_string.a: $(OBJ)
	ar rc $@ $(OBJ)
	ranlib $@

test: s21_string.a $(TEST_OBJ)
	$(CC) $(FLAGS) $(TEST_OBJ)  s21_string.a  -o ./unit_tests $(CHECK_FLAGS)
	./unit_tests

gcov_report: s21_string.a $(GCOV_TEST_OBJ) $(TEST_OBJ) 
	$(CC) $(FLAGS) $(GCOV_FLAGS) $(GCOV_TEST_OBJ)  $(TEST_OBJ) -o ./gcov_unit_tests $(CHECK_FLAGS)
	./gcov_unit_tests
	lcov -t "s21_string_test" -o s21_test.info -c -d .
	genhtml -o report s21_test.info

%.o: %.c 
	$(CC) -c $(FLAGS) $< -o $@

%.o: tests/%.c
	$(CC) -c $(FLAGS) $<  -o $@

gcov_%.o: %.c
	$(CC) -c $(FLAGS) $(GCOV_FLAGS) $<  -o ./$@

clang:
	cp ../materials/linters/.clang-format .clang-format
	clang-format -i *.c *.h tests/*.c tests/*.h
	rm .clang-format

clean:
	rm -f *.o 
	rm -rf *.gcno *.gcda gcov_unit_tests unit_tests *.info report/ s21_string.a

rebuild: clean all