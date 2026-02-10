CC = gcc
CFLAGS = -Wall -Werror -Wextra -c -std=c11

all:
	make s21_matrix.a

s21_matrix.a:
	$(CC) $(CFLAGS) funcs/*.c
	ar rcs s21_matrix.a *.o
	rm *.o

test: s21_matrix.a
	$(CC) $(CFLAGS) tests/*.c
	$(CC) -L. -I. -o test *.o s21_matrix.a `pkg-config --cflags --libs check`

gcov_report:
	mkdir -p report
	$(CC) $(CFLAGS) -fprofile-arcs -ftest-coverage funcs/*.c
	ar rcs s21_matrix_gcov.a *.o
	ranlib s21_matrix_gcov.a
	rm *.o
	$(CC) $(CFLAGS) -fprofile-arcs -ftest-coverage tests/*.c
	$(CC) -L. -I. -o test_gcov *.o s21_matrix_gcov.a -lgcov -pthread -lcheck_pic -lrt -lm -lsubunit
	./test_gcov
	gcov -o . funcs/*.c
	lcov -b ./ -d . --gcov-tool /usr/bin/gcov -c -o output.info --no-external
	genhtml -o report/ output.info

clean:
	rm *.o *.a *.gcno *.gcda *.gcov *.info *.log test
	rm -rf report

rebuild: 
	make clean
	make all
