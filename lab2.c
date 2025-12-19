#include <stdio.h>



int ways(int n){

    if(n<0) return 0;
    if (n==0) return 1;
    if (n==1) return 1;


    return ways(n-1)+ways(n-2);




}



int main(){
    int N;
    scanf("%d",&N);
    if (N<0){
        return 0;
    }
    int k = ways(N);
    printf("%d",k);

    return 0;



}


