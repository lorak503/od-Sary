#include <stdio.h>
#include <thread>
#include <unistd.h>

#include <mutex>
#include <time.h>

std::mutex mtx;

void count(int *in_circle, int how_many_points){
    
    float random_x;
    float random_y;
 
    for (int i =0 ;i < how_many_points; ++i){
       
        random_x = (float)(rand()%1000)/1000;
        random_y = (float)(rand()%1000)/1000;
        random_x*=random_x;
        random_y*=random_y;
        mtx.lock();
            if (random_x+random_y<=1.0){
                (*in_circle)++;
            }
        mtx.unlock();
    }

}

int main (int argc, char **argv){
    if (argc>1){
        
        int N = atoi(argv[1]);
        int n = 0;

        std::clock_t tStart = clock();
        std::thread first(count,&n,N);
        first.join();
        printf("Time taken 1 CPU: %.2f\n", (double)(clock() - tStart));
        printf("%lf\n",4*(float)n/(float)N);
       
        n = 0;
        printf("%f",tStart);
        tStart = clock();
        printf("%f\n",tStart);
        std::thread first_1(count,&n,N/2);
        std::thread second_1(count,&n,N/2);
        first_1.join();
        second_1.join();
        printf("Time taken 2 CPU: %.2f\n", (double)(clock() - tStart));
        printf("%lf\n",4*(float)n/(float)N);
      
        
        n=0;

        tStart = clock();
        std::thread first_2(count,&n,N/4);
        std::thread second_2(count,&n,N/4);
        std::thread third_2(count,&n,N/4);
        std::thread fourth_2(count,&n,N/4);
        first_2.join();
        second_2.join();
        third_2.join();
        
        fourth_2.join();
        printf("Time taken 4 CPU: %.2f\n", (double)(clock() - tStart));
        printf("%lf\n",4*(float)n/(float)N);
        
    }
    return 0;
}