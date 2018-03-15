make: src/bitonic_sort.c
	gcc -o bitonic_sort src/bitonic_sort.c -g -Wall -fopenmp

run: make
	./bitonic_sort 5000
	./bitonic_sort 5000
	./bitonic_sort 5000
	./bitonic_sort 50000
	./bitonic_sort 50000
	./bitonic_sort 50000
	./bitonic_sort 100000
	./bitonic_sort 100000
	./bitonic_sort 100000
	./bitonic_sort 200000
	./bitonic_sort 200000
	./bitonic_sort 200000
	./bitonic_sort 400000
	./bitonic_sort 400000
	./bitonic_sort 400000

test: make
	./bitonic_sort 400000 2
	./bitonic_sort 400000 4
	./bitonic_sort 400000 8
	./bitonic_sort 400000 16
	./bitonic_sort 400000 32
	./bitonic_sort 400000 64
	./bitonic_sort 400000 128
