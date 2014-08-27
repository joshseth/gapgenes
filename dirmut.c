#include <stdio.h>
#include <string.h>
#include <gsl/gsl_rng.h>
#include <dirent.h>


/* argv[1] is directory of to-be-mutated sequences (e.g gen-0) and argv[2] is 
an initially empty directory where mutated versions of sequences go (e.g. mut-gen-0) */

unsigned int gsl_ran_bernoulli (const gsl_rng * , double );  
/* gsl version of bernoulli distributed random variate */


int main (int argc, char *argv[]){


	int n;
	/* n is number of individual sequences in directory/population */
	int j;
	struct dirent **curgen;

	double mutr = 0.001;
	/* mutation rate */
    

	n = scandir (argv[1], &curgen, NULL, alphasort); 

	char newpath[n-2][150000];
	char mutpath[n-2][150000];

	for (j = 0; j < n-2; j++) {

		char command[50];
                strcpy (command, "export GLS_RNG_SEED=$RANDOM");
                system (command);

		gsl_rng_env_setup(); 


		gsl_rng *rng = gsl_rng_alloc(gsl_rng_default);

		sprintf (newpath[j], "%s/%s", argv[1], curgen[j+2]->d_name);
		printf("%s\n", newpath[j]);
		
		sprintf (mutpath[j], "%s/%s-%s-%d.%s" , argv[2], argv[2], "seq", j, "txt");
		printf("%s\n", mutpath[j]);
		
		char genearray[150000];
		
		FILE *fp;
		fp = fopen (newpath[j], "rt");
		fread (genearray, 1, 130251, fp);

		FILE *f;
		f = fopen(mutpath[j], "w");

		int i;

			for (i = 0; i < 130251; i++) {
	//	long seed;
	//	seed = gsl_rng_mt19937;   
	//	srand (seed); 
	//  	gsl_rng_set (rng, seed);      
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

    fprintf(f, "%s", genearray);
    gsl_rng_free(rng);
    fclose(fp);
    fclose(f);



	}

	return 0;

}
