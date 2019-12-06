#include <stdio.h>
#include <omp.h>
#include <cstdlib>
#include <ctime>

int main(void){
    int N = 1000000000;
    int counter = 0; 
    //scanf("%d",&N);
    int threads_numb = omp_get_num_threads();
    for (int threads = 0; threads<threads_numb; ++threads ){
        double start = omp_get_wtime();
        #pragma omp parallel reduction (+:counter)
        {
            unsigned seed = time(NULL) + omp_get_thread_num();
            #pragma omp for
                for (int i = 0; i<N ;++i){
                    double x = (double)rand_r(&seed)/RAND_MAX;
                    double y = (double)rand_r(&seed)/RAND_MAX;
                    if (x*x+y*y <= 1.0 ){
                        counter ++;
                    }
                }
        }
        printf("%d: PI = %.10f (%f)\n",threads_numb,4.0*counter/N, omp_get_wtime()-start);
    }
   
    
    return  0;   
}