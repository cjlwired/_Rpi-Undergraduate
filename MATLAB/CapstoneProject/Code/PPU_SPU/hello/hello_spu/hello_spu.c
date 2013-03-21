#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/time.h>

const int KSIZE = 3;
const int MSIZE = 129;
const UBOUND = 10;

float bound_check (int r, int c, int matrix[MSIZE][MSIZE])
{
	if ((r < 0) | (c < 0) | (r >= MSIZE) | (c >= MSIZE))
		return 0.0;

	return matrix[r][c];
}

int main(unsigned long long speid, unsigned long long argp, unsigned long long envp)
{
	// initialze image matrix variables
	int image_matrix[MSIZE][MSIZE];
	int kernel[KSIZE][KSIZE];
	int C[MSIZE][MSIZE];
	int i, j;
	int matrix_print = 1; // 1 = true, 0 = false

	// initialize random number generator functions and variables
	double num, r_num;
	srand((unsigned int) time(NULL));

	// print start Cell message
	printf("Start Cell # %lld, address (0x%llx)\n", argp, speid);
	
	// fill image with random values
	for (i = 0; i < MSIZE; i++)
	{
		for (j = 0; j < MSIZE; j++)
		{
			r_num = ((double)rand() / ((double) (RAND_MAX) + (double) 1));
			num = (r_num * UBOUND);
			C[i][j] = 0;
			image_matrix[i][j] = (int)num;
		}
	}
	
	// initialize kernel matrix
	for (i = 0; i < KSIZE; i++)
		for (j = 0; j < KSIZE; j++)
			kernel[i][j] = 1;
		
	// perform convolution
	float k_sum, m_sum;
	
	k_sum = 0.0;

	for (i = 0; i < KSIZE; i++)
		for (j = 0; j < KSIZE; j++)
			k_sum += kernel[i][j];

	int r, c;

	for (r = 0; r < MSIZE; r++)
	{
		for (c = 0; c < MSIZE; c++)
		{
			m_sum = 0.0;

			// row 1 of sliding window calculations
			m_sum += kernel[0][0] * bound_check(r-1,c-1,image_matrix);
			m_sum += kernel[0][1] * bound_check(r-1,c,image_matrix);
			m_sum += kernel[0][2] * bound_check(r-1,c+1,image_matrix);

			// row 2 of sliding window calculations
			m_sum += kernel[1][0] * bound_check(r,c-1,image_matrix);
			m_sum += kernel[1][1] * bound_check(r,c,image_matrix);
			m_sum += kernel[1][2] * bound_check(r,c+1,image_matrix);

			// row 3 of sliding window calculations
			m_sum += kernel[2][0] * bound_check(r+1,c-1,image_matrix);
			m_sum += kernel[2][1] * bound_check(r+1,c,image_matrix);
			m_sum += kernel[2][2] * bound_check(r+1,c+1, image_matrix);

			// assign the average of the sum to the current  pixel location in the matrix
			C[r][c] = m_sum / k_sum;
		}
	}
		
	// print finished Cell message
	printf("Finished Cell # %lld, address (0x%llx) finished computation\n", argp, speid);      

	//print_matrix(C);

	return 0;
}

void print_matrix(int matrix[MSIZE][MSIZE])
{
	int row, col;

	for (row = 0; row < MSIZE; row++)
	{
		for (col = 0; col < MSIZE; col++)
		{
			printf("%lld, ", matrix[row][col]);
		}
		printf("\n");
	}
}
