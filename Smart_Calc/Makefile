SRCS = s21_smartCalc.c HelpfulFunc.c SyntaxCheck.c
OBJS = ${SRCS:.c=.o}
CC = gcc
CFLAGS = -Wall -Werror -Wextra -g
BD = ../build/
OS=$(shell uname)
ifeq ($(OS), Linux)
	FLAGS=-lcheck -lm -lsubunit -lrt -lpthread -lm
	LEAKS = valgrind --leak-check=full
else
	FLAGS =-lcheck
	LEAKS = CK_FORK=no leaks --atExit --
endif

INSTALLDIR=../build
BUILDDIR=../build
ifeq ($(OS), Linux)  
TMPEXECUTABLE=Calculator
else ifeq ($(OS), Darwin)
TMPEXECUTABLE=Calculator.app/Contents/MacOS/Calculator
endif
	
all: build

build: clean mk replication
	cd $(BD); qmake SmartCalc.pro
	make -C $(BD

install: build
	mkdir $(HOME)/Desktop/SmartCalc_v1.0/
	cp -rf $(BD)SmartCalc.app $(HOME)/Desktop/SmartCalc_v1.0/
	make clean
uninstall:
	rm -rf  $(HOME)/Desktop/SmartCalc_v1.0/

dist:
	cd $(BD); cd ..; tar -cvf Calculator.tar build


dvi: 
	open -a "Google Chrome" description.html


s21_smartCalc.o:
	${CC} -c ${SRCS} -lm -g 

rebuild: clean
	${CC} ${SRCS} check.c -lm -g -o main.o
	./main.o

tests: clean s21_smartCalc.o
	checkmk clean_mode=1 tests.check > s21_smartCalc-test.c
	@gcc --coverage s21_smartCalc-test.c check.c $(FLAGS) ${SRCS} -o test && ./test

gcov_report: test
	@lcov -t "test" -o test.info -c -d .
	@genhtml -o report test.info
	
clean:
	/bin/rm -rf *.o test *.tar *.gcno *gcda report *.info *.out s21_smartCalc-test.c CPPLINT.cfg $(BUILDDIR)

checks: cppcheck style

style: clean
	cp ../materials/linters/CPPLINT.cfg CPPLINT.cfg
	python3 ../materials/linters/cpplint.py --extensions=c $(SRCS) check.c 

cppcheck: tests
	cppcheck --enable=all --suppress=missingIncludeSystem $(SRCS) check.c 
leaks: tests
	${LEAKS}  ./test

mk:
	mkdir ../build

replication:
	cp SmartCalc.pro $(BD)
	cp -R Icons $(BD)
	cp -R Font $(BD)
	cp *.c *.h *.cpp *.ui $(BD)

.PHONY: clean s21_smartCalc.a gcov_report unit_test leaks cppcheck style test build


