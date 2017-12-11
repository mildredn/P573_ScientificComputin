//norm2.c calculates L2-norm for a vector

#include <stdio.h>
#include <math.h>

double norm2(int n, double* x){
    int i = 0;
    double alpha = 0.0;
    
    if(x == NULL)
        return 0.0;
    
    for(i = 0; i < n; i++){
        alpha += x[i] * x[i];
    }
    
    alpha = sqrt(alpha);
    return alpha;
}