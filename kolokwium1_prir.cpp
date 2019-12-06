#include <stdio.h>
#include <omp.h>

double rect(double x){
    return 1.0/(1.0+x*x);
}

int main (void){  
    double a,b,h;
    double sum = 0.0;
    int N = 0;
    int i;
    printf("\nN:");
    scanf("%d",&N);
    printf("a:");
    scanf("%lf",&a);
    printf("\nb:");
    scanf("%lf",&b);


    if(N>0&&a<b){
        h = ((b-a)/(double) N);
        
        #pragma omp parallel for private(i) reduction(+:sum) 
        for (i=0;i<N;++i){
            sum += rect(a+i*h)*h;
        } 
        printf("\nsum: %lf ",sum);
    }else{
        printf("N nie jest wieksze od 0 lub a nie jest mniejsze od b");
    }
}
