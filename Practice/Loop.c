#include <stdio.h>
#include <time.h>

int main(){
    long long ans=1;
    float ticks= clock();
    for(int i=1; i<=100; i++){
        ans=1;
        for(int j=2; j<=i; j++){
            ans=ans*j;
        }
        //printf("%d ---%lld\n", i,ans);
    }
    ticks= clock()-ticks;
    printf("%f", (float)ticks/CLOCKS_PER_SEC);
    //0.000023
}