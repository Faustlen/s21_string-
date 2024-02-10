CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11 
GCOVFLAG = -Wall -Wextra -Werror -std=c11 -fprofile-arcs -ftest-coverage s21_string.c

UNAME=$(shell uname -s)

ifeq ($(UNAME), Darwin)
    CLIBS = -lcheck -lm
else
	CLIBS = -lcheck -lpthread -lm -lrt -lsubunit s21_string.a
endif

.PHONY: all clean test s21_string.a gcov_report

all: s21_string.a test gcov_report 
s21_string.a:
	$(CC) -c s21_string.c -o s21_string.o
	$(CC) -c s21_sprintf.c -o s21_sprintf.o
	$(CC) -c s21_strlen.c -o s21_strlen.o
	ar r s21_string.a *.o
test: s21_string.a
	$(CC) $(CFLAGS) test.c $(CLIBS) -o test
	./test
gcov_report: 
	$(CC) $(GCOVFLAG) test.c $(CLIBS) -o test
	./test
	lcov -t "test" -o test.info -c -d . 
	genhtml -o report test.info
	rm -f *.o *.gcda *.gcno *.gcov test.info
clean:
	rm -f *.a *.o test *.gcda *.gcno *.gcov coverage.info *.html rm -Rfv report
