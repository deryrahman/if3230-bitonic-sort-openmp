make: src/bitonic_sort.c
	gcc -o bitonic_sort src/bitonic_sort.c -g -Wall -fopenmp

run: src/bitonic_sort.c
	gcc -o bitonic_sort src/bitonic_sort.c -g -Wall -fopenmp
	./bitonic_sort 5000 > data/ex_time_5000_1.txt
	./bitonic_sort 5000 > data/ex_time_5000_2.txt
	./bitonic_sort 5000 > data/ex_time_5000_3.txt
	./bitonic_sort 50000 > data/ex_time_50000_1.txt
	./bitonic_sort 50000 > data/ex_time_50000_2.txt
	./bitonic_sort 50000 > data/ex_time_50000_3.txt
	./bitonic_sort 100000 > data/ex_time_10000_1.txt
	./bitonic_sort 100000 > data/ex_time_10000_2.txt
	./bitonic_sort 100000 > data/ex_time_10000_3.txt
	./bitonic_sort 200000 > data/ex_time_20000_1.txt
	./bitonic_sort 200000 > data/ex_time_20000_2.txt
	./bitonic_sort 200000 > data/ex_time_20000_3.txt
	./bitonic_sort 400000 > data/ex_time_40000_1.txt
	./bitonic_sort 400000 > data/ex_time_40000_2.txt
	./bitonic_sort 400000 > data/ex_time_40000_3.txt

test: src/bitonic_sort.c
	gcc -o bitonic_sort src/bitonic_sort.c -g -Wall -fopenmp
	./bitonic_sort 5000 -1 > data/test_ex_time_5000.txt
	./bitonic_sort 50000 -1 > data/test_ex_time_50000.txt
	./bitonic_sort 100000 -1 > data/test_ex_time_100000.txt
	./bitonic_sort 200000 -1 > data/test_ex_time_200000.txt
	./bitonic_sort 400000 -1 > data/test_ex_time_400000.txt

test2: src/bitonic_sort.c
	gcc -o bitonic_sort src/bitonic_sort.c -g -Wall -fopenmp
	./bitonic_sort 5000 1
	./bitonic_sort 5000 1
	./bitonic_sort 5000 1
	./bitonic_sort 5000
	./bitonic_sort 5000
	./bitonic_sort 5000
	./bitonic_sort 50000 1
	./bitonic_sort 50000 1
	./bitonic_sort 50000 1
	./bitonic_sort 50000
	./bitonic_sort 50000
	./bitonic_sort 50000
	./bitonic_sort 100000 1
	./bitonic_sort 100000 1
	./bitonic_sort 100000 1
	./bitonic_sort 100000
	./bitonic_sort 100000
	./bitonic_sort 100000
	./bitonic_sort 200000 1
	./bitonic_sort 200000 1
	./bitonic_sort 200000 1
	./bitonic_sort 200000
	./bitonic_sort 200000
	./bitonic_sort 200000
	./bitonic_sort 400000 1
	./bitonic_sort 400000 1
	./bitonic_sort 400000 1
	./bitonic_sort 400000
	./bitonic_sort 400000
	./bitonic_sort 400000
