#include <stdio.h>
#include <thread>
#include <unistd.h>
#include <future>
#include <mutex>
#define MAX_ITERATION 1000000
//https://en.cppreference.com/w/cpp/thread/condition_variable
std::mutex mtx;
void foo(int *start,int *stop){
	for (int i = 1; i < MAX_ITERATION+1; i++){
        mtx.lock();
        (*start)++;
        if (*start%100000==0)
            *stop = 1;
        mtx.unlock();
    }
}

void bar(int *start){
	for (int i = 0; i < MAX_ITERATION ; i++){
	    mtx.lock();
        (*start)++;
        mtx.unlock();
    }
}

int main(void){

	int firstB = 0;
    int stop = 0;
	std::thread first(foo,&firstB,&stop);
	std::thread second(foo,&firstB,&stop);
	while(true){
        if (stop){
            printf("%d\n",firstB);
            stop = 0;

        }
        if (firstB == 2000000)
            break;
    }
    first.join();
    second.join();

    printf("%d\n",firstB);
}
