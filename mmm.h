#ifndef MMM_H_
#define MMM_H_

// shared globals
extern unsigned int mode;
extern unsigned int size, num_threads;
extern double **A, **B, **SEQ_MATRIX, **PAR_MATRIX;
typedef struct mmm_params
{
  int start;
  int end;
} mmm_params;

void mmm_init();
void set_matrices(double***);
void fill_matrix(double**);
void mmm_reset(double **);
void mmm_freeup();
void free_matrix(double**);
void mmm_seq();
void* mmm_par();
void* calculate(void*);
double mmm_verify();

#endif /* MMM_H_ */
