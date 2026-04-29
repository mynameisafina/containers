FLAGS = -Wextra -Werror -Wall -std=c++17
LDFLAGS = $(shell pkg-config --cflags --libs gtest)
TESTFLAGS=-lgtest

all: clean test

clean:
	rm -rf main *.dSYM test *.o *.a *.gcda *.gcno *.info *.out *.txt report .clang_format report.html

test: clean
	g++ --coverage $(FLAGS) tests/* $(TESTFLAGS) -o test
	./test

style:
	cp ../materials/linters/.clang-format ./
#	clang-format -i tests/*.cc *.h
	clang-format -n tests/*.cc *.h
	rm .clang-format

valgrind: test
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=RESULT_VALGRIND.txt ./test

leaks:
	leaks -atExit -- ./test

gcov_report: test
	lcov --no-external -t "test" -o report.info -c -d .
	genhtml -o report.html report.info
	rm *.gcda *.gcno
	open report.html/index.html 2>/dev/null
