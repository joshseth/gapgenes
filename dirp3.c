#include <stdio.h>
#include <string.h>
#include <gsl/gsl_rng.h>
#include <time.h>
#include <dirent.h>
#include <math.h>

int compare_floats (const void *a, const void *b) 
/* sorts largest entries towards the top of the array, 
i.e. array[0] > array[1]  */
    {
      const float *da = (const float *) a;
      const float *db = (const float *) b;
     
      return (*da < *db) - (*da > *db);
    }


char genearray[1000];

int main(int argc, char *argv[]) {
/* argv[1] is "phenotype" directory of rms scores */ 
/* argv[2] is the directory of mutated sequences who's respective phenotypes are in argv[1] */
/* argv[3] is the initially EMPTY directory for the newly created and recombined genomes, i.e /gen-3 if argv[2] is /mut-gen-2, etc */	

	struct dirent **vent;
	int n;
	int cnt;

	struct dirent **ent;
	int m;

	time_t t;
	srand ((unsigned) time(&t));

	n = scandir (argv[1], &vent, NULL, alphasort); 
	m = scandir (argv[2], &ent, NULL, alphasort);  
	
	char buffer[n][150000];
	char mut_genome[n][15000];
	int rms[10] = {0};
	float exp_fitness[10] = {0};
	int survive[10] = {0};
	int r[10] = {0};
	float threshold[10] = {0};

	if (n >= 0){
		for (cnt = 2; cnt < n; ++cnt){
			
			printf ("%s\n", vent[cnt]->d_name);
			sprintf (buffer[cnt], "%s/%s", argv[1], vent[cnt]->d_name);

			sprintf (mut_genome[cnt], "%s/%s", argv[2], ent[cnt]->d_name);
			
			FILE *fp;
			fp = fopen(buffer[cnt],"rt");
			
			fscanf (fp, "rms = %d", &rms[cnt-2]);
			/* ^just edited, check */
			printf ("%d\n", rms[cnt-2]);


			exp_fitness[cnt-2] = exp (- abs (rms[cnt-2] - 25));
			printf ("%f\n", exp_fitness[cnt-2]);

			threshold[cnt-2] = exp_fitness[cnt-2];
			

			survive[cnt-2] = pow (exp_fitness[cnt-2], -1);
			printf ("%d\n", survive[cnt-2]);

			r[cnt-2] = rand()%survive[cnt-2];
			printf ("%d\n", r[cnt-2]);
			
			fclose(fp);

		}
	}

	qsort (threshold, 10, sizeof(int), compare_floats);
	int i;
	for (i = 0; i < 10; i++){
		if (r[i] !=0 && exp_fitness[i] <= threshold[2]){
		remove(mut_genome[i+2]);
		}
	}

	struct dirent **surv;
	int num_surv = scandir (argv[2], &surv, NULL, alphasort) - 2;
	// printf ("%s %i\n", "number of survivors: ", num_surv );
	
	/* START of RECOMBINATION */

		char textfile[13791];
    	char textfile2[13791];

		int j;
		char newpath[10][1000];

		for (j = 0; j < 10; j++) {
			FILE *newborn;
			sprintf (newpath[j], "%s/%s-%s-%d.%s", argv[3], argv[3], "seq", j, "txt");
			newborn = fopen (newpath[j], "w");
			
			FILE *fr;
    		FILE *f;
    		int cot;

			int x = rand()%num_surv + 2;
			int y = rand()%num_surv + 2;

    		char parone[1000];
    		char partwo[1000];	
			sprintf (parone, "%s/%s", argv[2], surv[x]->d_name);
			sprintf (partwo, "%s/%s", argv[2], surv[y]->d_name);

			fr = fopen(parone,"rt");
    		f  = fopen(partwo, "rt");

    		fread(textfile, 1, 13791, fr);
    		fread(textfile2, 1, 13791, f);

			int r1 = rand()%2;
	    	int r2 = rand()%2;
	    	int r3 = rand()%2;
	    	int r4 = rand()%2;

		    for (cot = 0; cot < 3701; cot++){  /* gene 1 */
		    	if (r1 == 1){
		    		fprintf(newborn, "%c", textfile[cot]);
		    	}
		    	if (r1 == 0){
		    		fprintf(newborn, "%c", textfile2[cot]);
		    	}
		    }
		    for (cot = 3702; cot < 6237; cot++){ /* gene 2 */
		    	if (r2 == 1){
		    		fprintf(newborn, "%c", textfile[cot]);
		    	}
		    	if (r2 == 0){
		    		fprintf(newborn, "%c", textfile2[cot]);
		    	}
		    }
		    for (cot = 6238; cot < 11779; cot++){ /* gene 3 */
		    	if (r3 == 1){
		    		fprintf(newborn, "%c", textfile[cot]);
		    	}
		    	if (r3 == 0){
		    		fprintf(newborn, "%c", textfile2[cot]);
		    	}
		    }
		    for (cot = 11780; cot < 13791; cot++){ /* gene 4 */
		    	if (r4 == 1){
		    		fprintf(newborn, "%c", textfile[cot]);
		    	}
		    	if (r4 == 0){
		    		fprintf(newborn, "%c", textfile2[cot]);
		    	}
		    }
		}  
	    



}





