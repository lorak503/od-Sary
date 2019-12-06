#include <stdio.h>
#include <omp.h>
#include <cstdlib>

struct point {
    double x; //real
    double y; //image
};

point add(point p1, point p2){
    point result;
    result.x = p1.x + p2.x;
    result.y = p1.y + p2.y;
    return result;
}

point multiply(point p1, point p2){
    point result;
    result.x = (p1.x*p2.x-p1.y*p2.y);
    result.y = (p1.x*p2.y+p1.y*p2.x);
    return result;
}

int mandelbrot(point p, int N){
    point z;
    z.x=0.0;
    z.y=0.0;
    
    if (N!=0){
        for (int i =0; i<N;i++){
          
            z = add(multiply(z,z),p);
            
            if ((z.x*z.x)+(z.y*z.y)>=4.0){
                return 0;
            }
        }
    }
    return 1;
}

int main(void){
    int array[180][120]={};
    int N=10000;

    
        
        #pragma omp parallel 
        {   
            point p;
            int threads_num = omp_get_num_threads();
            int thread_num = omp_get_thread_num();
            
            for (int i=thread_num ; i<120 ; i+=threads_num){
                
                for (int j=0; j<180 ; ++j){
                    p.y = 1.0 - (i*(1.0/60.0));
                    p.x = -2.0 + (j*(1.0/60.0));
                    
                    array[j][i] = mandelbrot(p,N);
                    
                }
                

            }

        }


    for (int i=0;i<120;++i){
        for (int j=0;j<180;++j){
            if (array[j][i]==1){
                printf("#");
            }else{
                printf(".");
            }
        }
        printf("\n");
    }
    return 0;
}