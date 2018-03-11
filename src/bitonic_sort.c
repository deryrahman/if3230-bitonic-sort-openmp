#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void print(int*, int);
void exchange(int*, int, int);
void rng(int*, int, int*);
void buildDummy(int*,int,int,int);
void impBitonicSort(int*, int, int);
int getPowTwo(int);

int main(int argc, char **argv) {
  if (argc < 3) {
    printf("Usage: %s n p\n  where n is problem size (power of two), p number of thread\n", argv[0]);
    exit(1);
  }

  int N = atoi(argv[1]);
  int thread = atoi(argv[2]);
  int dummyN = getPowTwo(N);
  int *arr = (int*) malloc(dummyN*sizeof(int));

  if(!arr){
    printf("Unable to allocate memory\n");
    exit(1);
  }

  int maxX;
  rng(arr,N,&maxX);
  buildDummy(arr,N,dummyN,maxX);
  // print(arr,N);
  clock_t begin = clock();
  impBitonicSort(arr,dummyN,thread);
  clock_t end = clock();
  double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
  printf("Time : %lf\n", time_spent);

  return 0;
}


void rng(int* arr, int n, int* maxX) {
    int seed = 13515097;
    srand(seed);
    for(long i = 0; i < n; i++) {
        arr[i] = (int)rand();
        *maxX = ((i==0 || *maxX<arr[i])?arr[i]:*maxX);
    }
}

void buildDummy(int* arr,int N,int dummyN, int maxX){
  for(long i = N; i < dummyN; i++) {
    arr[i]=maxX;
  }
}

void print(int* a, int N) {
  int i;
  for (i = 0; i < N; i++) {
    printf("%d\n", a[i]);
  }
  printf("\n");
}

void exchange(int* a, int i, int j) {
  a[i]=a[i]^a[j];
  a[j]=a[i]^a[j];
  a[i]=a[j]^a[i];
  // int t;
  // t = a[i];
  // a[i] = a[j];
  // a[j] = t;
}

void impBitonicSort(int* a, int N, int thread) {

  int i,j,k;

  for (k=2; k<=N; k=2*k) {
    for (j=k>>1; j>0; j=j>>1) {
      #pragma omp parallel for num_threads(thread)
      for (i=0; i<N; i++) {
        int ij=i^j;
        if ((ij)>i) {
          if ((i&k)==0 && a[i] > a[ij]) exchange(a,i,ij);
          if ((i&k)!=0 && a[i] < a[ij]) exchange(a,i,ij);
        }
      }
    }
  }
}


int getPowTwo(int n){
  int d=1;
  while (d>0 && d<n) d<<=1;
  return d;
}
