#include <stdio.h>
#include <time.h>

long long factorial (int n){
    if(n==0 || n==1) return 1;
    else return (long long)n*factorial(n-1);
}

int main(){
    long long ans;
    float ticks=clock();

    for(int i=1; i<=100; i++) ans= factorial(i);
    ticks= clock()-ticks;

    printf("%f", (float)ticks/CLOCKS_PER_SEC);
    //0.000045

}