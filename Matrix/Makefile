SRCS = s21_matrix.c
OBJS = ${SRCS:.c=.o}
CC = gcc
CFLAGS = -Wall -Werror -Wextra
OS=$(shell uname)
ifeq ($(OS), Linux)
	FLAGS=-lcheck -lm -lsubunit -lrt -lpthread
else
	FLAGS =-lcheck
endif

all: clean s21_matrix.a test

s21_matrix.a:
	${CC} -c ${SRCS}
	@ar rcs s21_matrix.a ${OBJS}
	@ranlib s21_matrix.a

test: clean s21_matrix.a
	checkmk clean_mode=1 tests.check > s21_matrix-test.c
	gcc -g s21_matrix-test.c -o test $(FLAGS) s21_matrix.a && ./test

gcov_report: s21_matrix.a
	@gcc --coverage s21_matrix-test.c -lcheck ${SRCS} -o unit-test
	@./unit-test
	@lcov -t "test" -o test.info -c -d .
	@genhtml -o report test.info
	
clean:
	@/bin/rm -rf *.o *.a test unit-test *.gcno *gcda report *.info *.out s21_matrix-test.c CPPLINT.cfg


checks: cppcheck style leaks

style: clean
	cp ../materials/linters/CPPLINT.cfg CPPLINT.cfg
	python3 ../materials/linters/cpplint.py --extensions=c *.c 

cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem . *.c *.h

leaks: test
	CK_FORK=no leaks --atExit -- ./test
	

.PHONY: s21_matrix.a gcov_report unit_test main leaks cppcheck style test tests
