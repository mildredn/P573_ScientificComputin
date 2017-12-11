//norm1.c calculates L1-norm for a vector

#include<stdio.h>
#include<math.h>

double norm1(int n, double* x){
    int i = 0;
    double alpha = 0.0;
    
    if(x == NULL)
        return 0.0;
    
    for(i = 0; i < n; i++){
        alpha += fabs(x[i]);
    }
    
    return alpha;
}