make: src/bitonic_sort.c
	gcc -o bitonic_sort src/bitonic_sort.c -g -Wall -fopenmp

test: src/bitonic_sort.c
	gcc -o bitonic_sort src/bitonic_sort.c -g -Wall -fopenmp
	./bitonic_sort 5000 > data/test_5000.txt
	./bitonic_sort 50000 > data/test_50000.txt
	./bitonic_sort 10000 > data/test_10000.txt
	./bitonic_sort 20000 > data/test_20000.txt
	./bitonic_sort 40000 > data/test_40000.txt
