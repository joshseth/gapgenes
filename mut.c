#include <stdio.h>
#include <string.h>
#include </home/rcf-40/jsschiff/gsl/include/gsl/gsl_rng.h>



unsigned int gsl_ran_bernoulli (const gsl_rng * , double );  /* gsl version of bernoulli distributed random variate */

void display_sequence() {
    FILE *fp;
    char genearray[130251];
    fp = fopen("/Users/Josh/Desktop/C-GAP-genes/seqN-2-2.txt","r");
    fread(genearray, 1, 130251, fp);
    printf("%s", genearray);
   fclose(fp);
 }

int main(int argc, char *argv[])
{
    gsl_rng_env_setup(); 



    int i;
    double mutr = 0.5;
    gsl_rng *rng = gsl_rng_alloc(gsl_rng_default);
    FILE *fp;
    char genearray[130251];
    fp = fopen(argv[1],"r");
    fread(genearray, 1, 130251, fp);
    // printf("%s", genearray);
    
    for (i = 0; i < 130251; i++) {
        unsigned int r = gsl_ran_bernoulli(rng, mutr);
        int rand1 = rand()%100;

        if (r == 1 && genearray[i] != '>' && genearray[i] != '\n') {
            genearray[i] = 'y';
        } 
        if (rand1 < 25 && genearray[i] =='y'){
            genearray[i] = 'A';

        }
        if (rand1 < 50 && rand1 >= 25 && genearray[i] == 'y'){
            genearray[i] = 'T';

        }
        if (rand1 >= 50 && rand1 < 75 && genearray[i] == 'y'){
            genearray[i] = 'C';

        }
        if (rand1 >= 75 && genearray[i] == 'y'){
            genearray[i] = 'G';
        }


    }

    printf("%s", genearray);
    gsl_rng_free(rng);
    fclose(fp);
    return 0;
}
