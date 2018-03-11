make: src/bitonic_sort.c
	gcc -o bitonic_sort src/bitonic_sort.c -g -Wall -fopenmp

test: src/bitonic_sort.c
	gcc -o bitonic_sort src/bitonic_sort.c -g -Wall -fopenmp
	./bitonic_sort 5000 -1
	./bitonic_sort 50000 -1
	./bitonic_sort 10000 -1
	./bitonic_sort 20000 -1
	./bitonic_sort 40000 -1
