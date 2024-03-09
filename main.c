#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include "rtclock.h"
#include "mmm.h"

// shared  globals
unsigned int mode;
unsigned int size, num_threads;
double **A, **B, **SEQ_MATRIX, **PAR_MATRIX;

int main(int argc, char *argv[]) {
	//sequential
	if(argc == 3 && strcmp(argv[1], "S") == 0){
		mode = 0;
		size = atoi(argv[2]);
		if(size == 0){
			printf("Improper Argument\n");
			return 0;
		}
		printf("========\nmode: sequential\nthread count: 1\nsize: %d\n========\n", size);
	}
	//parallel
	else if(argc == 4 && strcmp(argv[1], "P") == 0){
		mode = 1;
		size = atoi(argv[3]);
		num_threads = atoi(argv[2]);
		if(size == 0 || num_threads == 0){
			printf("Improper Argument\n");
			return 0;
		}
		else if(num_threads < 0 || num_threads > 32){
			printf("Improper Number of Threads\n");
			return 0;
		}
		else if(size < 1 || size > 10000000){
			printf("Matrix Size is below 1\n");
			return 0;
		}
		printf("========\nmode: parallel\nthread count: %d\nsize: %d\n========\n", num_threads, size);
	}
	else{
		printf("Improper Argument\n");
	}

	// initialize matrices
	mmm_init();

	double clockstart, clockend, clocktotal = 0;

	if(mode == 0){
		for(int i = 0; i < 3; i++){
			clockstart = rtclock();	// start the clock
			mmm_seq();
			clockend = rtclock(); // stop the clock
			clocktotal = clocktotal + clockend - clockstart;
		}
		printf("Sequential Time (avg of 3 runs): %.6f sec\n", (clocktotal/3));
	}
	else if(mode == 1){
		for(int i = 0; i < 3; i++){
			clockstart = rtclock();	// start the clock
			mmm_seq();
			clockend = rtclock(); // stop the clock
			clocktotal = clocktotal + clockend - clockstart;
		}
		printf("Sequential Time (avg of 3 runs): %.6f sec\n", (clocktotal/3));

		double clocktotal_par = 0;

		for(int i = 0; i < 3; i++){
			clockstart = rtclock();	// start the clock
			mmm_par();
			clockend = rtclock(); // stop the clock
			clocktotal_par = clocktotal_par + clockend - clockstart;
		}
		printf("Parallel Time (avg of 3 runs): %.6f sec\n", (clocktotal_par/3));

		double speedup = clocktotal/clocktotal_par;
		printf("Speedup: %.6f\n", speedup);

		// free some stuff up
		printf("Verifying...");
		double dif = mmm_verify();
		printf("largest error between parallel and sequential matrix: %.6f\n", dif);
	}

	mmm_freeup();
	return 0;
}
