#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mpi.h"

int NDIM;
int NUM_SIM; 
int UPDATE;
int NMAX;
FILE *FP_Log;
char benchmark_path[200];
char benchmark_case[40];
char benchmark_res[40];
double **RANGE_Paras;
double **INIT_Paras;
double *INIT_Metrics;
double **Paras;
double *Metrics;
double *PARAS_Sum;

void init();

int 
main(int argc, char **argv)
{
   int rank, size;


   MPI_Init(&argc, &argv);

   MPI_Comm_size(MPI_COMM_WORLD, &size);
   MPI_Comm_rank(MPI_COMM_WORLD, &rank);
   //printf("Hello World, I am %d of %d \n", rank, size);

   //read the configration
   if(rank == 0){
   		init();
   }

   MPI_Finalize();
   return 0;
}

void init()
{
   int i, j;
    FILE *fp_init;
    time_t now;
    struct tm *timenow;
    char log_name[40];


    if(!(fp_init = fopen("downhill_config", "r"))){
        printf("downhill_config file does not exsit!\n");
        exit(1);
    }


    //read max iterator
    fscanf(fp_init, "%d", &NMAX);

    //read parameters dimension
    fscanf(fp_init, "%d", &NDIM);

    //read benchmark configuration
    fscanf(fp_init, "%s", &benchmark_path);
    fscanf(fp_init, "%s", &benchmark_case);
    fscanf(fp_init, "%s", &benchmark_res);
    printf("%s\n", benchmark_path);
    printf("%s\n", benchmark_case);
    printf("%s\n", benchmark_res);

    //allocate parameters range and intinial values
    RANGE_Paras  = (double **)malloc(NDIM * sizeof(double *));
    INIT_Paras   = (double **)malloc((NDIM + 1) * sizeof(double *));
    Paras        = (double **)malloc((NDIM + 1) * sizeof(double *));
    INIT_Metrics = (double *)malloc((NDIM + 1) * sizeof(double));
    Metrics      = (double *)malloc((NDIM + 1) * sizeof(double));
    PARAS_Sum    = (double *)malloc(NDIM * sizeof(double));

    for(i = 0; i < NDIM; i++){
        RANGE_Paras[i] = (double *)malloc(2 * sizeof(double));
    }
    for(i = 0; i < NDIM + 1; i++){
        INIT_Paras[i] = (double *)malloc((NDIM) * sizeof(double));
        Paras[i]      = (double *)malloc((NDIM) * sizeof(double));
    } 

    fclose(fp_init);

    //init log
    time(&now);
    timenow = localtime(&now);
    sprintf(log_name, "simplex_log_%d.%d.%d-%d.%d.%d", timenow->tm_year+1900, \
            timenow->tm_mon, timenow->tm_mday, timenow->tm_hour, timenow->tm_min,\
            timenow->tm_sec);
    FP_Log  = fopen(log_name, "aw");
    fprintf(FP_Log,"iterator+action+parameters+metrics\n");

    NUM_SIM = NDIM + 1;   
}