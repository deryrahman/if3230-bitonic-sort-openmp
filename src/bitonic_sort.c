#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <string.h>
#include <omp.h>

struct timeval st, et;
void swap(int*, int, int);
void rng(int*, int, int*);
void buildDummy(int*, int, int, int);
void impBitonicSort(int*, int, int);
int getPowTwo(int);
void executeTest(int*, int);
void execute(int*, int, int);
void writeToFile(int*, int, char*);

int main(int argc, char **argv) {
  int n, dummyN, threads, test, maxX;
  int* arr;

  // get maximum effective threads
  threads = omp_get_max_threads();

  if (argc < 2) {
    printf("Usage: %s <n> <p>\nwhere <n> is problem size, <p> is number of thread (optional)\n\n", argv[0]);
    exit(1);
  }

  if (argc == 3){
    // use for custom threads number
    threads = atoi(argv[2]);
  }
  // true for test with 1,2,4,8,...,256 threads number
  test = threads<=0;

  // get problem size;
  n = atoi(argv[1]);
  // get dummyN from nearest power of two
  dummyN = getPowTwo(n);

  // prepare random numbers
  arr = (int*) malloc(dummyN*sizeof(int));
  if(!arr){
    printf("Unable to allocate memory\n");
    exit(1);
  }
  rng(arr,n,&maxX);
  buildDummy(arr,n,dummyN,maxX);

  // write random numbers to input file
  writeToFile(arr,n,"./data/input");

  if(test){
    executeTest(arr,dummyN);
  } else {
    execute(arr,dummyN,threads);
  }

  // write sorted numbers to output file
  writeToFile(arr,n,"./data/output");
  free(arr);
  return 0;
}

void writeToFile(int* arr, int n, char* path){
  FILE* f = fopen(path,"w");
  for(int i=0; i<n; i++) {
      fprintf(f, "%d\n", arr[i]);
  }
  fclose(f);
}

void execute(int* arr, int dummyN, int threads){
  gettimeofday(&st,NULL);
  impBitonicSort(arr,dummyN,threads);
  gettimeofday(&et,NULL);
  int elapsed = ((et.tv_sec - st.tv_sec) * 1000000) + (et.tv_usec - st.tv_usec);
  printf("Execution time: %d micro sec\n",elapsed);
}

void executeTest(int* arr, int dummyN){
  int* tmp;
  tmp = (int*)malloc(dummyN*sizeof(int));
  if(!tmp){
    printf("Unable to allocate memory\n");
    exit(1);
  }
  for(int t=1; t<=256; t<<=1){
    memcpy(tmp,arr,dummyN*sizeof(int));
    printf("With thread %d\n", t);
    gettimeofday(&st,NULL);
    impBitonicSort(tmp,dummyN,t);
    gettimeofday(&et,NULL);

    int elapsed = ((et.tv_sec - st.tv_sec) * 1000000) + (et.tv_usec - st.tv_usec);
    printf("Execution time: %d micro sec\n",elapsed);
  }
  memcpy(arr,tmp,dummyN*sizeof(int));
  free(tmp);
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

void swap(int* a, int i, int j) {
  int t;
  t = a[i];
  a[i] = a[j];
  a[j] = t;
}

void impBitonicSort(int* a, int N, int threads) {
  int i,j,k;

  for (k=2; k<=N; k=2*k) {
    for (j=k>>1; j>0; j=j>>1) {
      // bitonic increasing
      #pragma omp parallel for num_threads(threads) private(i) shared(N,j,k)
      for (i=0; i<N; i++) {
        int ij=i^j;
        if ((ij)>i) {
          // monotonic increasing
          if ((i&k)==0 && a[i] > a[ij]) swap(a,i,ij);
          // monotonic decreasing
          if ((i&k)!=0 && a[i] < a[ij]) swap(a,i,ij);
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
