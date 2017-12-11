//norminf.c calculates inf-norm for a vector
#include<stdio.h>
#include<math.h>

double norminf(int n, double* x){
    int i = 0;
    double alpha = 0.0;
    
    if(x == NULL)
        return 0.0;
    
    for(i = 0; i < n; i++){
        alpha = alpha < fabs(x[i]) ? fabs(x[i]) : alpha;
    }
    
    return alpha;
}