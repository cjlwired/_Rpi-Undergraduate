// PS3DSIVE Matrix Benchmark Code

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int inverse_matrix()
{

	// Initialize random number generator functions and variables.

	double num, r;
	srand((unsigned int) time(NULL));

	int uBound = 128;

	// Initialize matrix variable specifications.

	float **A, **I, val;
	int i, j, k, matsize;
	
	// Entire the size of the square matrix from the command line:

	printf("Enter the size of the matrix (i.e. value of 'n' as size is n x n): ");
	scanf ("%d", &matsize);
	printf("\n");

	// Allocate dynamic memory for matrix A of size (matsize x matsize)

	A =(float **)malloc(matsize*sizeof(float *)); 	

	for(i = 0; i < matsize; i++)
		A[i] = (float *)malloc(matsize*sizeof(float));

	// Allocate dynamic memory for matrix I, the identity matrix, of size (matsize x matsize)

	I = (float **)malloc(matsize*sizeof(float *));

	for(i = 0; i < matsize; i++)
		I[i] = (float *)malloc(matsize*sizeof(float));

	// Randomly assign integers between 0-128 to the matrix elements:

	for (i = 0; i < matsize; i++)
	{
		for (j = 0; j < matsize; j++)
		{
			r = ((double)rand() / ((double)(RAND_MAX)+(double)(1)));
			num = (r * uBound);
			A[i][j] = (int)num;
		}
	}

	// Automatically initialize the identity matrix.

	for (i = 0; i < matsize; i++)		// | 1 0 0 . . 0 |		
		for (j = 0;j < matsize; j++)	// | 0 1 0 . . 0 |		      
			if (i == j)					// | 0 0 1 . . 0 |
				I[i][j] = 1;			// | . . . . . 0 |
			else						// | . . . . 1 0 |
				I[i][j] = 0;			// | 0 0 0 0 0 1 |

	/*

	//Print matrix A, pre-inverse operations:

	printf("Here is the randomly generated matrix:\n");

	for(i = 0; i < matsize; i++)
	{
		for (j = 0; j < matsize; j++)
			printf("%f	", A[i][j]);

		printf("\n");
	}

	*/

	// Instantiate timer variables:

	clock_t start, end;
								
	// Measure the time before the inverse matrix operations begin:

	printf ("\nStarting matrix timer before calculating inverse.\n\n");

	start = clock();

	// Loop used to calculate the inverse of matrix A:

		// Through these calculations, the identity matrix I will contain the inverse at the end.
	
	for (k = 0; k < matsize;k++)
	{
		val = A[k][k];		

		for (j = 0; j < matsize; j++)
		{
			A[k][j] /= val;			
			I[k][j] /= val;				
		}								
		for (i = 0; i < matsize; i++)			
		{
			val = A[i][k];	

			for (j = 0; j < matsize; j++)
			{							
				if(i == k)
					break;
				A[i][j] -= A[k][j] * val;
				I[i][j] -= I[k][j] * val;
			}
		}
	}

	/*

	//Print matrix I, which now contains the inverse of matrix A.
	
	printf("The inverse of the matrix is:\n");	 

	for(i=0;i<matsize;i++)
	{
		for(j=0;j<matsize;j++)
			printf("%f	",I[i][j]);
		printf("\n");
	}

	*/

	// Measure the time after the inverse matrix calculations are completed:

	end = clock();
	
	// Calculate the time difference used by the process

	float time_diff = ((float)(end - start))/CLOCKS_PER_SEC;

	// Print out specifications.

	printf ("Matrix calculations are completed - the operation took a total of:\n\n");
	printf ("%f seconds.\n\n", time_diff);

	return 0;
}

// ************************************************************************//
// Generalized to print out the matrix if needed:

	/*
	
    for(i = 0; i < matsize; i++)
	{
		for (j = 0; j < matsize; j++)
			printf("%f	", A[i][j]);

		printf("\n");
	}

	*/
