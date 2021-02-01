#include <stdio.h>
#include <time.h>

long long int lookup[101];

long long factorial (int n){
    if(n==0 || n==1) return lookup[n]=1;
    else return lookup[n]=(long long)n*lookup[n-1];
}

int main(){
    long long ans;
    float ticks=clock();
    for(int i=1; i<=100; i++) {
        ans= factorial(i);
        //printf("%lld\n", ans);
    }
    ticks= clock()-ticks;
    printf("%f", (float)ticks/CLOCKS_PER_SEC);
    //0.000004
}