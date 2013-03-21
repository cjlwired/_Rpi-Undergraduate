#include <stdio.h>
#include <libspe2.h>
#include <pthread.h>
#include <stdlib.h>
#include <errno.h>
#include "time.h"
#include <vec_types.h>
#include <mfcio.h>

extern spe_program_handle_t * hello_spu;

struct thread_args
{
	struct spe_context * spe;
	//unsigned long long argp[129][129]__attribute__((__aligned__(16)));
	unsigned long long argp[129][129];
	unsigned long long envp;
};

void my_spe_thread(struct thread_args * arg)
{
	unsigned int runflags = 0;
	unsigned int entry = SPE_DEFAULT_ENTRY;
	spe_stop_info_t *stopinfo;
        int error;

	// run SPE context
	error = spe_context_run(arg->spe, &entry, runflags, arg->argp, arg->envp, &stopinfo);

	if (error == 0)
		printf("SPE program called exit() indicate a normal exit\n");
	else
		printf("SPE program returned an error\n");
	
	//done - now exit thread
	pthread_exit(NULL);
}

int main()
{
	int i, j;
	pthread_t pts;
	spe_context_ptr_t spe;
	struct thread_args t_arg;
	unsigned long long local_matrix[129][129];
	
	for (i = 0; i < 129; i++)
		for (j = 0; j < 129; j++)
		{
			local_matrix[i][j] = 5;
			t_arg.argp[i][j] = 5;			
		}

	mfc_put(local_matrix, t_arg.argp, t_arg.envp, 1, 0, 0);

	// open SPE program
	hello_spu = spe_image_open("./hello_spu/hello_spu");

	// create SPE context
	spe = spe_context_create(0, NULL);

	// load SPE program
	spe_program_load(spe, hello_spu);
	
	t_arg.spe = spe;
	t_arg.envp = 467;

	pthread_create(&pts, NULL, &my_spe_thread, &t_arg);

	// Wait for SPU-thread to complete execution
	pthread_join(pts, NULL);

	// close SPE program
	spe_image_close(hello_spu);

	// destroy SPE context
	spe_context_destroy(spe);

	return 0;
}

void print_array(int array[129][129])
{
	int row;

	for (row = 0; row < 129; row++)
		printf("%d, ", array[row]);

	printf("\n");
}

void print_matrix(unsigned long long matrix[129][129])
{
	int row, col;

	for (row = 0; row < 129; row++)
	{
		for (col = 0; col < 129; col++)
		{
			printf("%lld, ", matrix[row][col]);
		}
		printf("\n");
	}

}
