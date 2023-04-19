FLAG = -Wall -Werror -Wextra -g
WAY_C = QT_part/smart_calc/bin

LIBS_MACOS = -L /usr/local/lib -lcheck
LIBS_LINUX = -lcheck -lsubunit -lpthread -lrt -lm -D_GNU_SOURCE

OS = $(shell uname)
ifeq ($(OS), Darwin)
OPEN = open gcov_report/index.html
LIBS = $(LIBS_MACOS)
LEAK_CHECK = leaks --atExit -- ./test
endif


all: 
	make -C QT_part/build-smart_calc-Desktop_Qt_5_15_2_GCC_64bit-Debug -f Makefile install

install: 
	make -C QT_part/build-smart_calc-Desktop_Qt_5_15_2_GCC_64bit-Debug -f Makefile install

sudo_install: 
	sudo make -C QT_part/build-smart_calc-Desktop_Qt_5_15_2_GCC_64bit-Debug -f Makefile install

uninstall:
	make -C QT_part/build-smart_calc-Desktop_Qt_5_15_2_GCC_64bit-Debug -f Makefile uninstall

sudo_uninstall:
	sudo make -C QT_part/build-smart_calc-Desktop_Qt_5_15_2_GCC_64bit-Debug -f Makefile uninstall

dvi:
	doxygen Doxyfile

open_dvi:
	open html/index.html

dist:
	tar --totals -cvf smart_calc.tar QT_part/build-smart_calc-Desktop_Qt_5_15_2_GCC_64bit-Debug/smart_calc

main: clean main.o list.a read_expression.a processing_errors.a
	gcc -o  build/main_test $(FLAG) main.o list.a read_expression.a `pkg-config --cflags --libs check`
	./build/main_test

main.o: main.c
	gcc -c $(FLAG) main.c

test: clean create_folder t_main.a t_list.a t_allocate_memory.a t_read_lexems.a t_expression.a t_sort_station.a t_calculation.a t_credit_calculator.a t_deposit_calculator.a list.a processing_errors.a allocate_memory.a expression.a calculation.a read_lexems.a sort_station.a credit_calculator.a deposit_calculator.a
	gcc -o build/test $(FLAG) obj/t_main.a obj/t_list.a obj/t_allocate_memory.a obj/t_read_lexems.a obj/t_expression.a obj/t_sort_station.a obj/t_calculation.a obj/t_credit_calculator.a obj/t_deposit_calculator.a obj/list.a obj/processing_errors.a obj/allocate_memory.a obj/expression.a obj/calculation.a obj/read_lexems.a obj/sort_station.a obj/credit_calculator.a obj/deposit_calculator.a `pkg-config --cflags --libs check` -lm
	./build/test

create_folder:
	mkdir build
	mkdir obj

list.a: 
	gcc -c $(FLAG) $(WAY_C)/list/list.c -o obj/list.o
	ar rcs obj/list.a obj/list.o -lm
	rm obj/list.o

read_expression.a: 
	gcc -c $(FLAG) read_expression.c -o obj/read_expression.o
	ar rcs obj/read_expression.a obj/read_expression.o
	rm obj/read_expression.o

processing_errors.a: 
	gcc -c $(FLAG) $(WAY_C)/processing_errors/processing_errors.c -o obj/processing_errors.o
	ar rcs obj/processing_errors.a obj/processing_errors.o
	rm obj/processing_errors.o

allocate_memory.a: 
	gcc -c $(FLAG) $(WAY_C)/allocate_memory/allocate_memory.c -o obj/allocate_memory.o
	ar rcs obj/allocate_memory.a obj/allocate_memory.o
	rm obj/allocate_memory.o

expression.a: 
	gcc -c $(FLAG) $(WAY_C)/expression/expression.c -o obj/expression.o
	ar rcs obj/expression.a obj/expression.o
	rm obj/expression.o

calculation.a: 
	gcc -c $(FLAG) $(WAY_C)/expression/calculation.c -o obj/calculation.o
	ar rcs obj/calculation.a obj/calculation.o
	rm obj/calculation.o

read_lexems.a: 
	gcc -c $(FLAG) $(WAY_C)/expression/read_lexems.c -o obj/read_lexems.o
	ar rcs obj/read_lexems.a obj/read_lexems.o
	rm obj/read_lexems.o

sort_station.a: 
	gcc -c $(FLAG) $(WAY_C)/sort_station/sort_station.c -o obj/sort_station.o
	ar rcs obj/sort_station.a obj/sort_station.o
	rm obj/sort_station.o

credit_calculator.a:
	gcc -c $(FLAG) $(WAY_C)/credit_calculator/credit_calculator.c -o obj/credit_calculator.o
	ar rcs obj/credit_calculator.a obj/credit_calculator.o
	rm obj/credit_calculator.o

deposit_calculator.a:
	gcc -c $(FLAG) $(WAY_C)/deposit_calculator/deposit_calculator.c -o obj/deposit_calculator.o
	ar rcs obj/deposit_calculator.a obj/deposit_calculator.o
	rm obj/deposit_calculator.o

t_main.a: 
	gcc -c $(FLAG) tests/tests_main.c -o obj/tests_main.o
	ar rcs obj/t_main.a obj/tests_main.o
	rm obj/tests_main.o

t_list.a: 
	gcc -c $(FLAG) tests/tests_list.c -o obj/tests_list.o
	ar rcs obj/t_list.a obj/tests_list.o
	rm obj/tests_list.o

t_allocate_memory.a: 
	gcc -c $(FLAG) tests/tests_allocate_memory.c -o obj/tests_allocate_memory.o
	ar rcs obj/t_allocate_memory.a obj/tests_allocate_memory.o
	rm obj/tests_allocate_memory.o

t_read_lexems.a: 
	gcc -c $(FLAG) tests/tests_read_lexems.c -o obj/tests_read_lexems.o
	ar rcs obj/t_read_lexems.a obj/tests_read_lexems.o
	rm obj/tests_read_lexems.o

t_expression.a: 
	gcc -c $(FLAG) tests/tests_expression.c -o obj/tests_expression.o
	ar rcs obj/t_expression.a obj/tests_expression.o
	rm obj/tests_expression.o

t_calculation.a: 
	gcc -c $(FLAG) tests/tests_calculation.c -o obj/tests_calculation.o
	ar rcs obj/t_calculation.a obj/tests_calculation.o
	rm obj/tests_calculation.o

t_sort_station.a: 
	gcc -c $(FLAG) tests/tests_sort_station.c -o obj/tests_sort_station.o
	ar rcs obj/t_sort_station.a obj/tests_sort_station.o
	rm obj/tests_sort_station.o

t_credit_calculator.a: 
	gcc -c $(FLAG) tests/tests_credit_calculator.c -o obj/tests_credit_calculator.o
	ar rcs obj/t_credit_calculator.a obj/tests_credit_calculator.o
	rm obj/tests_credit_calculator.o

t_deposit_calculator.a: 
	gcc -c $(FLAG) tests/tests_deposit_calculator.c -o obj/tests_deposit_calculator.o
	ar rcs obj/t_deposit_calculator.a obj/tests_deposit_calculator.o
	rm obj/tests_deposit_calculator.o

clean:
	make -C QT_part/build-smart_calc-Desktop_Qt_5_15_2_GCC_64bit-Debug -f Makefile clean
	rm -rf main_test test *.txt *.a *.o *.dSYM *.gch
	rm -rf obj/main_test obj/test obj/*.txt obj/*.a obj/*.o obj/*.dSYM obj/*.gch
	rm -rf build/main_test build/test build/*.txt build/*.a build/*.o build/*.dSYM build/*.gch
	rm -rf build obj gcov_report

doxygen_install_ubuntu:
	sudo apt-get install doxygen
	sudo apt-get install doxygen graphviz

# GCOV part

open_gcov_report:
	open gcov_report/index.html

gcov_report: clean create_folder gcov_t_main.a gcov_t_list.a gcov_t_allocate_memory.a gcov_t_read_lexems.a gcov_t_expression.a gcov_t_sort_station.a gcov_t_calculation.a gcov_t_credit_calculator.a gcov_t_deposit_calculator.a gcov_list.a gcov_processing_errors.a gcov_allocate_memory.a gcov_expression.a gcov_calculation.a gcov_read_lexems.a gcov_sort_station.a gcov_credit_calculator.a gcov_deposit_calculator.a
	gcc --coverage -o test obj/t_main.a obj/t_list.a obj/t_allocate_memory.a obj/t_read_lexems.a obj/t_expression.a obj/t_sort_station.a obj/t_calculation.a obj/t_credit_calculator.a obj/t_deposit_calculator.a obj/list.a obj/processing_errors.a obj/allocate_memory.a obj/expression.a obj/calculation.a obj/read_lexems.a obj/sort_station.a obj/credit_calculator.a obj/deposit_calculator.a `pkg-config --cflags --libs check` -lm
	./test
	lcov -t 'gcov_report' -o gcov_report.info -c -d .
	genhtml -o gcov_report gcov_report.info

gcov_list.a: 
	gcc -c $(FLAG) $(WAY_C)/list/list.c -o obj/list.o
	ar rcs obj/list.a obj/list.o -lm
	rm obj/list.o

gcov_read_expression.a: 
	gcc -c $(FLAG) read_expression.c -o obj/read_expression.o --coverage
	ar rcs obj/read_expression.a obj/read_expression.o
	rm obj/read_expression.o

gcov_processing_errors.a: 
	gcc -c $(FLAG) $(WAY_C)/processing_errors/processing_errors.c -o obj/processing_errors.o --coverage
	ar rcs obj/processing_errors.a obj/processing_errors.o
	rm obj/processing_errors.o

gcov_allocate_memory.a: 
	gcc -c $(FLAG) $(WAY_C)/allocate_memory/allocate_memory.c -o obj/allocate_memory.o --coverage
	ar rcs obj/allocate_memory.a obj/allocate_memory.o
	rm obj/allocate_memory.o

gcov_expression.a: 
	gcc -c $(FLAG) $(WAY_C)/expression/expression.c -o obj/expression.o --coverage
	ar rcs obj/expression.a obj/expression.o
	rm obj/expression.o

gcov_calculation.a: 
	gcc -c $(FLAG) $(WAY_C)/expression/calculation.c -o obj/calculation.o --coverage
	ar rcs obj/calculation.a obj/calculation.o
	rm obj/calculation.o

gcov_read_lexems.a: 
	gcc -c $(FLAG) $(WAY_C)/expression/read_lexems.c -o obj/read_lexems.o --coverage
	ar rcs obj/read_lexems.a obj/read_lexems.o
	rm obj/read_lexems.o

gcov_sort_station.a: 
	gcc -c $(FLAG) $(WAY_C)/sort_station/sort_station.c -o obj/sort_station.o --coverage
	ar rcs obj/sort_station.a obj/sort_station.o
	rm obj/sort_station.o

gcov_credit_calculator.a:
	gcc -c $(FLAG) $(WAY_C)/credit_calculator/credit_calculator.c -o obj/credit_calculator.o --coverage
	ar rcs obj/credit_calculator.a obj/credit_calculator.o
	rm obj/credit_calculator.o

gcov_deposit_calculator.a:
	gcc -c $(FLAG) $(WAY_C)/deposit_calculator/deposit_calculator.c -o obj/deposit_calculator.o --coverage
	ar rcs obj/deposit_calculator.a obj/deposit_calculator.o
	rm obj/deposit_calculator.o

gcov_t_main.a: 
	gcc -c $(FLAG) tests/tests_main.c -o obj/tests_main.o --coverage
	ar rcs obj/t_main.a obj/tests_main.o
	rm obj/tests_main.o

gcov_t_list.a: 
	gcc -c $(FLAG) tests/tests_list.c -o obj/tests_list.o --coverage
	ar rcs obj/t_list.a obj/tests_list.o
	rm obj/tests_list.o

gcov_t_allocate_memory.a: 
	gcc -c $(FLAG) tests/tests_allocate_memory.c -o obj/tests_allocate_memory.o --coverage
	ar rcs obj/t_allocate_memory.a obj/tests_allocate_memory.o
	rm obj/tests_allocate_memory.o

gcov_t_read_lexems.a: 
	gcc -c $(FLAG) tests/tests_read_lexems.c -o obj/tests_read_lexems.o --coverage
	ar rcs obj/t_read_lexems.a obj/tests_read_lexems.o
	rm obj/tests_read_lexems.o

gcov_t_expression.a: 
	gcc -c $(FLAG) tests/tests_expression.c -o obj/tests_expression.o --coverage
	ar rcs obj/t_expression.a obj/tests_expression.o
	rm obj/tests_expression.o

gcov_t_calculation.a: 
	gcc -c $(FLAG) tests/tests_calculation.c -o obj/tests_calculation.o --coverage
	ar rcs obj/t_calculation.a obj/tests_calculation.o
	rm obj/tests_calculation.o

gcov_t_sort_station.a: 
	gcc -c $(FLAG) tests/tests_sort_station.c -o obj/tests_sort_station.o --coverage
	ar rcs obj/t_sort_station.a obj/tests_sort_station.o
	rm obj/tests_sort_station.o

gcov_t_credit_calculator.a: 
	gcc -c $(FLAG) tests/tests_credit_calculator.c -o obj/tests_credit_calculator.o --coverage
	ar rcs obj/t_credit_calculator.a obj/tests_credit_calculator.o
	rm obj/tests_credit_calculator.o

gcov_t_deposit_calculator.a: 
	gcc -c $(FLAG) tests/tests_deposit_calculator.c -o obj/tests_deposit_calculator.o --coverage
	ar rcs obj/t_deposit_calculator.a obj/tests_deposit_calculator.o
	rm obj/tests_deposit_calculator.o

cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem .

valgrind:
	valgrind --leak-check=full --track-origins=yes --log-file=_valgrind-out.txt build/test
