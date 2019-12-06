#include <stdio.h>
#include <omp.h>
///  g++ openmp.cpp  -fopenmp
/// OMP_NUM_THREADS= ./a.out
int main(int argc, char* argv[]){

    #pragma omp parallel  for ordered
    for (int i =0; i< omp_get_num_threads();i++)
    #pragma omp ordered
    {
        int id = omp_get_thread_num();
        int total = omp_get_num_threads();
       
        printf("Jestem #%d z #%d\n",id,total);
    }
    printf("Zakonczenie \n");
    return 0;
}