/* main.c includes the driver program to test and time norm1, norm2, and norminf functions defined in norm1.c, norm2.c and norminf.c respectively
*/

#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <math.h>
#include "norms.h" //contains definition of norm1, norm2, norminf

int main(){
   
    int nstart = 0,  nstride = 0, nend = 0, counter, i;
    double nflops = 0.0, nreps, temp, norm_1, norm_2, norm_inf;
    double start = 0.0, elapsed = 0.0, finish = 0.0;
    double* x;
    double a = DBL_MAX;
    FILE* fp, *fp1;
    
    //open file "sizes" to read nstart, nstride, nend, and nflops
    fp = fopen("sizes", "r");
    fscanf(fp, "%d %d %d %le", &nstart, &nstride, &nend, &nflops);
    
    fclose(fp);
    
    //open results file
    fp1 = fopen("results", "w");
    
    for(counter = nstart; counter <= nend; counter += nstride){

        //Assign double array named x
        x = (double*) malloc(sizeof(double) * counter);
        
        //Generate random double values in x -- reference links : https://stackoverflow.com/questions/13408990/how-to-generate-random-float-number-in-c
        //and https://stackoverflow.com/questions/30064616/understanding-dbl-max
        for(i = 0; i < counter; i++){
            x[i] = ((double)rand()/(double)(RAND_MAX)) * a;
        }
        
        nreps = nflops/2.0 * counter > 1.0 ? nflops/2.0 * counter : 1.0;
        temp = nreps;
        
        //timing norm1
        
        start = elapsedtime();
        
        while(temp >= 0){
            norm_1 = norm1(counter, x);
            temp--;
        }
        finish = elapsedtime();
        elapsed = (finish - start)/nreps; //time taken to execute norm1
        
        
        fprintf(fp1, "%d %.17f %.17f %d\n", counter, elapsed, nreps, 1);
        
        //timing norm2
        
        temp = nreps;
        start = elapsedtime();
        
        while(temp >= 0){
            norm_2 = norm2(counter, x);
            temp--;
        }
        
        finish = elapsedtime();
        elapsed = (finish - start)/nreps; //time taken to execute norm2
        
        fprintf(fp1, "%d %.17f %.17f %d\n", counter, elapsed, nreps, 2);
        
        //timing norm-inf
        
        temp = nreps;
        start = elapsedtime();
        
        while(temp >= 0){
            norm_inf = norminf(counter, x);
            temp--;
        }
        
        finish = elapsedtime();
        elapsed = (finish - start)/nreps; //time taken to execute norminf
        
        fprintf(fp1, "%d %.17f %.17f %d\n", counter, elapsed, nreps, 3);
       
       
        free(x);
    }
    
    fclose(fp1);
    return 0;
}