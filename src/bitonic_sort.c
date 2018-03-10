#include <stdio.h>
#include <stdlib.h>

void swap(int* a, int* b){
  *a=*a^*b;
  *b=*a^*b;
  *a=*b^*a;
}

void bitSwap(int* a, int* b, int dir){
  if(*a>*b == dir){
    swap(a,b);
  }
}

int getPowTwo(int n){
  int d=1;
  while (d>0 && d<n) d<<=1;
  return d>>1;
}

void bitMerge(int* arr, int lo, int n, int dir){
  if(n>1){
    int m = getPowTwo(n);
    for(int i=lo; i<lo+n-m; i++){
      bitSwap(arr+i, arr+(i+m), dir);
    }
    bitMerge(arr, lo, m, dir);
    bitMerge(arr, lo+m, n-m, dir);
  }
}

void bitSort(int* arr, int lo, int n, int dir){
  if(n>1){
    int m = n/2;
    bitSort(arr, lo, m, !dir);
    bitSort(arr, lo+m, n-m, dir);
    bitMerge(arr, lo, n, dir);
  }
}

void rng(int* arr, int n) {
    int seed = 13515097; // Ganti dengan NIM anda sebagai seed.
    srand(seed);
    for(long i = 0; i < n; i++) {
        arr[i] = (int)rand();
    }
}

int main(int argc, char const *argv[]) {
  int N = atoi(argv[1]);
  int arr[N];
  rng(arr,N);
  bitSort(arr,0,N,1);

  for(int i=0; i<N; i++){
    printf("%d\n", arr[i]);
  }
  return 0;
}
