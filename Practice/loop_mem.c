#include <stdio.h>
#include <time.h>

int main(){
    long long ans;
    float ticks=clock();
    long long int lookup[101];
    lookup[0]=lookup[1]=1;
    for(int i=1; i<=100; i++) {
        ans=lookup[i]=i*lookup[i-1];
        
       // printf("%lld\n", ans);
    }
    ticks=clock()-ticks;
    printf("%f", (float)ticks/ CLOCKS_PER_SEC);
    //0.000003
}