// PS3DSIVE Matrix Convolution Code
// --- Convolve a 256x256 matrix with a given 3x3 kernel. ---

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int matrix_print = 0;	// Global boolean to print out matrices.

const int KSIZE = 3;		// Define size of kernel matrix.
const int MSIZE = 255;		// Define size of image matrix.

// Function checks bound for each element and returns the corresponding element.

int bound_check (int r, int c, int **M)
{

	if ((r < 0) | (c < 0) | (r >= MSIZE) | (c >= MSIZE))
		return 0;
	

	return M[r][c];

}

// Main Loop Function

int main(int argc, char ** argv)
{
	if (argc!= 12)
	{
			printf ("\nNot enough arguments!\n\n");
			exit(1);
	}

	// Initialize matrix variable specifications.

	char t[MSIZE+1];

	int **C, **K, **M;
	int i, j;

	// Initialize file input/output pointers from command line.

	FILE *f;
	FILE *o;

	f = fopen(argv[1], "r"); // Open image  file.
	o = fopen(argv[2], "w"); // Open output file.

	// Initialize the image matrix, dynamically allocate memory, and assign random values.

	// printf ("A matrix of size NxN as defined in the code is now being instantiated.\n\n");

	M =(int **)malloc(MSIZE*sizeof(int *)); 	

	for(i = 0; i < MSIZE; i++)
		M[i] = (int *)malloc(MSIZE*sizeof(int));

	// Read in values from the input file and assign them to the convolution matrix.

	for (i = 0; i < MSIZE; i++)
	{
		for (j = 0; j < MSIZE; j++)
		{
			fscanf(f,"%s", t);
			M[i][j] = atoi(t);
		}
	}
	
	// Print out the randomly defined matrix.
	
	if (matrix_print)
	{

		printf ("Here is the randomly generated matrix:\n\n");

		for (i = 0; i < MSIZE; i++)
		{
			for (j = 0; j < MSIZE; j++)
			{
				printf ("%.0d\t", M[i][j]);
			}

			printf("\n");
		}

		printf("\n");
	}
	
	// Read in kernel matrix values from the command line.

	K =(int **)malloc(KSIZE*sizeof(int *)); 

	for(i = 0; i < KSIZE; i++)
		K[i] = (int *)malloc(KSIZE*sizeof(int));

	K[0][0] = atoi(argv[3]);
	K[0][1] = atoi(argv[4]);
	K[0][2] = atoi(argv[5]);
	K[1][0] = atoi(argv[6]);
	K[1][1] = atoi(argv[7]);
	K[1][2] = atoi(argv[8]);
	K[2][0] = atoi(argv[9]);
	K[2][1] = atoi(argv[10]);
	K[2][2] = atoi(argv[11]);


	printf("\n");

	// Print out kernel matrix.

	if (matrix_print)
	{

		printf("Here is kernel matrix you entered:\n\n");

		for (i = 0; i < KSIZE; i++)
		{
			for (j = 0; j < KSIZE; j++)
			{
				printf ("%d\t", K[i][j]);
			}
	
			printf("\n");
		}
	}

	// Instantiate timer variables:

	clock_t start, end;

	// Perform the matrix convolution sliding window procedure. First dynamically allocate memory.
	// Start with value at [1,1] and end at value [N-2,N-2] where N is the size of the matrix. 
	// This is a brute force summation implementation of the code.

	// Allocate memory for convolved matrix.

	C =(int **)malloc(MSIZE*sizeof(int *)); 	

	for(i = 0; i < MSIZE; i++)
		C[i] = (int *)malloc(MSIZE*sizeof(int));

	int k_sum, m_sum;

	k_sum = 0;

	// Calculate the sum of all elements in the sliding window. This value will be used to calculate the new pixel value.

	for (i = 0; i < KSIZE; i++)
		for (j = 0; j < KSIZE; j++)
			k_sum += K[i][j];



	int r,c;	// Represents matrix row (r) and column (c)

	start = clock();

	for (r = 0; r < MSIZE; r++)
	{
		for (c = 0; c < MSIZE; c++)
		{
			m_sum = 0;

			// Row 1 of sliding window calculation.

			m_sum += K[0][0] * bound_check(r-1,c-1,M);
			m_sum += K[0][1] * bound_check(r-1,c,M);
			m_sum += K[0][2] * bound_check(r-1,c+1,M);

			// Row 2 of sliding window calculation.

			m_sum += K[1][0] * bound_check(r,c-1,M);
			m_sum += K[1][1] * bound_check(r,c,M);
			m_sum += K[1][2] * bound_check(r,c+1,M);

			// Row 3 of sliding window calculation.

			m_sum += K[2][0] * bound_check(r+1,c-1,M);
			m_sum += K[2][1] * bound_check(r+1,c,M);
			m_sum += K[2][2] * bound_check(r+1,c+1,M);

			// Assign the average of the sum to the current pixel location in the matrix.

			C[r][c] = m_sum / k_sum;
		}
	}

	// Measure the time after the inverse matrix calculations are completed:

	end = clock();

	printf("\n");

	// Print out the new matrix M after convolution.

	if (matrix_print)
	{

		printf("Here is the new matrix C after convolution:\n\n");

		for (i = 0; i < MSIZE; i++)
		{
			for (j = 0; j < MSIZE; j++)
			{
				printf ("%d\t", C[i][j]);
			}

			printf("\n");
		}

	}

	// Calculate the time difference used by the process

	int time_diff = (end - start)/(CLOCKS_PER_SEC);

	// printf ("\nConvolution for a matrix of size %d takes: %.3f sec.\n\n", MSIZE, time_diff);

	// Print out convolution matrix to output file

	for (i = 0; i < MSIZE; i++)
	{
		for (j = 0; j < MSIZE; j++)
		{
			fprintf(o,"%d ", C[i][j]);
		}

		fprintf(o,"\n");
	}

	fclose(f);
	fclose(o);

	// Free all memory created by the program.

	for (i = 0; i < KSIZE; i++)
		free(K[i]);

	for (i = 0; i < MSIZE; i++)
	{
		free(C[i]);
		free(M[i]);
	}

	return 0;

}