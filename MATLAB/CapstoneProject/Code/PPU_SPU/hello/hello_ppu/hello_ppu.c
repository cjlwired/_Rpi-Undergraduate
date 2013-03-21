#include "libspe2.h"
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>

extern spe_program_handle_t hello_spu;

int main(void)
{
        spe_context_ptr_t speid;
        unsigned int flags = 0;
        unsigned int entry = SPE_DEFAULT_ENTRY;
        void *argp = NULL;
        void *envp = NULL;
        spe_stop_info_t stop_info;
        int rc;
	spe_program_handle_t *program;

	program = spe_image_open("../hello_spu/hello_spu");

	if (!program)
	{
		perror("spe_open_image");
		return -1;
	}

        printf("Hello world!\n");

        // Create an SPE context
        speid = spe_context_create(flags, NULL);

        if (speid == NULL)
        {
                perror("spe_context_create");
                return -2;
        }

        // Load an SPE executable object into the SPE context local store

        if (spe_program_load(speid, program))
        {
                perror("spe_program_load");
                return -3;
        }

        // Run the SPE context
        rc = spe_context_run(speid, &entry, 0, argp, envp, &stop_info);

        if (rc < 0) 
        {
                perror("spe_context_run");
        }
        
        // Destroy the SPE context
        spe_context_destroy(speid);
      
        return 0;
}
