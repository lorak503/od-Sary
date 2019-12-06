#include <stdio.h>
#include <omp.h>
#include <cmath>

double count(double x){
    return sqrt(1.0-(x*x));
}

int main (void){  
    double a,b,step,sum;
    const int number_of_steps = 100000;
    int i;

    scanf("%lf",&a);
    scanf("%lf",&b);
    step = ((b-a)/(double) number_of_steps);
   
    sum = 0.0;
    #pragma omp parallel for private(i) reduction(+:sum) 
    for (i=0;i<=number_of_steps;++i){
        sum += count(a+i*step)*step;
    } 
    printf("%lf ",sum);
}