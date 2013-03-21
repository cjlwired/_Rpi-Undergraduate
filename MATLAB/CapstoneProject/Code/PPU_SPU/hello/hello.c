#include <stdio.h>
#include <libspe2.h>
#include <pthread.h>
#include <stdlib.h>
#include <errno.h>
#include "time.h"

extern spe_program_handle_t * hello_spu;
//#define SPU_THREADS 6
#define SPU_THREADS 4

struct thread_args
{
	struct spe_context * spe;
	unsigned long long argp;
	unsigned long long envp;
};

void my_spe_thread(struct thread_args * arg)
{
	unsigned int runflags = 0;
	unsigned int entry = SPE_DEFAULT_ENTRY;
	
	// run SPE context
	spe_context_run(arg->spe, &entry, runflags, arg->argp, arg->envp, NULL);
	
	//done - now exit thread
	pthread_exit(NULL);
}

int main()
{
	clock_t start, end;

	printf("START!!!\n");
	
	pthread_t pts[SPU_THREADS];
	spe_context_ptr_t spe[SPU_THREADS];
	struct thread_args t_args[SPU_THREADS];
	int value[SPU_THREADS];
	int i;

	// open SPE program
	hello_spu = spe_image_open("./hello_spu/hello_spu");

	start = clock();

	// create SPE-thread to execute 'hello_spu.'
	for (i = 0; i < SPU_THREADS; i++)
	{
		// create SPE context
		spe[i] = spe_context_create(0, NULL);

		// load SPE program
		spe_program_load(spe[i], hello_spu);
	
		// create pthread
		t_args[i].spe = spe[i];
		t_args[i].argp = i;
		t_args[i].envp = NULL;

		pthread_create( &pts[i], NULL, &my_spe_thread, &t_args[i]);
	}

	// Wait for SPU-thread to complete execution
	for (i = 0; i < SPU_THREADS; i++)
	{
		//printf("SPU_THREADS running\n");
		pthread_join(pts[i], NULL);
	}	

	end = clock();
	
	// close SPE program
	printf("\nThe program has successfully executed.\n");
	spe_image_close(hello_spu);

	// destroy SPE contexts
	for (i = 0; i < SPU_THREADS; i++)
	{
		spe_context_destroy(spe[i]);
	}

	// Calculate the time difference used by the process
	float time_diff = (end - start)/((float)CLOCKS_PER_SEC);

	// Print out time
	printf("\nConvolution for a matrix of size %d takes: %.7f sec.\n\n", 129, time_diff);

	return 0;
}
