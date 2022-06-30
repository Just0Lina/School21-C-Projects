SRCS = s21_math.c
	
OBJS = ${SRCS:.c=.o}
CC = gcc
CFLAGS = -Wall -Werror -Wextra

all: clean s21_math.a test

s21_math.a: ${SRCS}
	${CC} ${CFLAGS} -c ${SRCS}
	@ar rcs s21_math.a ${OBJS}
	@ranlib s21_math.a

test: s21_math.a unit_test

unit_test:
	${CC} ${CFLAGS} -c s21_math-test.c
	${CC} ${CFLAGS} s21_math-test.o s21_math.a -lcheck -o test
	./test

gcov_report: s21_math.a
	@gcc --coverage s21_math-test.c -lcheck ${SRCS} -o unit-test
	@./unit-test
	@lcov -t "test" -o test.info -c -d .
	@genhtml -o report test.info
	
clean:
	@/bin/rm -rf *.o *.a test unit-test *.gcno *gcda report *.info main

checks: cppcheck leaks style

style:
	python3 ../materials/linters/cpplint.py --extensions=c *.c *.h

cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem . *.c

leaks: s21_math-test.c
	CK_FORK=no leaks --atExit -- ./test
	
main: s21_math.a main.c
	${CC} ${CFLAGS} main.c s21_math.a -o main

run: main
	./main

create_tests: compile
	@./test_builder > s21_math-test.check
	@checkmk s21_math-test.check > s21_math-test.c
	@/bin/rm test_builder
	
compile:
	@gcc test_builder.c -o test_builder
