#include <stdio.h>
#include <omp.h>
#include <cstdlib>
#include <ctime>




///  g++ openmp.cpp  -fopenmp
/// OMP_NUM_THREADS= ./a.out
void count(int *in_circle, int how_many_points,int step,int total){
    
    float random_x;
    float random_y;
    unsigned int seed = time(NULL);
    for (int i =step ;i < how_many_points; i+=total){
       
        float random_x = static_cast <float> (rand_r(&seed)) / static_cast <float> (RAND_MAX);
        float random_y = static_cast <float> (rand_r(&seed)) / static_cast <float> (RAND_MAX);
        random_x*=random_x;
        random_y*=random_y;
       
            if (random_x+random_y<=1.0){
            #pragma omp atomic
            
                (*in_circle)++;
            
            }
        
    }

}

int main(int argc, char **argv){
    if (argc>1){
        int N = atoi(argv[1]);
        int n = 0;
        int total;
        double start;
        double end;
        start = omp_get_wtime();

        #pragma omp parallel          
        {
            int id = omp_get_thread_num();
            total = omp_get_num_threads();
        
            printf("Jestem #%d z #%d\n",id,total);
            count(&n,N,id,total);
        }
        end = omp_get_wtime();
        printf("Work took %f sec. time.\n", end-start);
        printf("\n%lf\n",4*(float)n/(float)N);
        printf("Zakonczenie \n");
    }
    return 0;
}