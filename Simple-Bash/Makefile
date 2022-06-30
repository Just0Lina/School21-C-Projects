OBJS = ${SRCS:.c=.o}
CC = gcc
CFLAGS = -Wall -Werror -Wextra

s21_cat:
	${CC} cat/s21_cat.c -o s21_cat

clean:
	@/bin/rm -rf *.o *.a

checks: cppcheck leaks style

testsCat: s21_cat
	bash cat/Script.sh

style:
	cp ../../materials/linters/CPPLINT.cfg CPPLINT.cfg
	python3 ../../materials/linters/cpplint.py --extensions=c */*.c */*.h

cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem . */*.c

leaksCat: s21_cat
	leaks --atExit -- ./s21_cat -benstv cat/tests/all_flag_tests/*


s21_grep:
	${CC} grep/s21_grep.c -o s21_grep

testsGrep: s21_grep
	bash grep/Script.sh

leaksGrep: s21_grep
	leaks --atExit -- ./s21_grep -ivnhsf cat grep/tests/b_flag_tests/*
