
#include <math.h>
#include <stdio.h>
#include <stdlib.h>


int BASELINE = 78;

int main (int argc, char ** argv)
{

	FILE *f;
	FILE *o;
	char r[256];
	char t[256];
	int m[255][255];
	int distances[255];
	int x = 0; 
	int y = 0;
	int found = 0;
	double sum = 0;
	int average = 0;
	int z = 0;
	double totalvariance = 0;
	int inbounds[255];
	int inboundcount = 0;
	double d = 0;
	double e = 0;
	if (argc != 3)
	{
		printf("Not enough arguments!\n");
		exit(1);
	}

	f = fopen(argv[1],"r");	// open image
	if (f == NULL)				// check for existence of file
		exit(1);



	for (y = 0; y < 255; y++)	// read all of the integers into a matrix
	{
		for (x = 0; x < 255; x++)
		{

			fscanf(f,"%s",t);
			m[y][x] = atoi(t);  // change this to atoi(t)/128 if the input is not already binary
		}
	}
printf("Distances:\n");
	for(x = 0; x < 255; x++)		// sweep across the x axis
	{
		for ( y = BASELINE; y < 255 && !found; y++)	// start searching at baseline, work way down
		{
			if ( m[y][x] == 1)						// find first white pixel
			{
				distances[x] = y - BASELINE;		// calculate distance from baseline
				found = 1;
				printf("%d ",y);
			}
		}
		found = 0;
	}
printf("\n\n\n");
	for(x = 0; x < 255; x++)		// calculate average distance
	{
		sum += distances[x];
printf("%f ",sum);
	}
	average = sum / 255;
printf("\nsum:%f   average: %f\n\nDifferences:\n",sum,average);

									// calculate standard deviation
	for(x = 2; x < 252; x++)		// ignore first/last 2 border pixels
	{
		z = distances[x] - average;
		d = z;
printf("%d ",d);
		totalvariance += z * d;  // summation of difference between distances and average
	}

	if (totalvariance != 0)
			
		totalvariance = sqrt(totalvariance/255);	// square root of sum of difference divided by N (255)
		

	o = fopen(argv[2],"a");	// open output file

	fprintf(o,"\nAverage Displacement: %d \nStandard Deviation: %.3f\n", average, totalvariance);

	sum = 0;						//reset sum
	for (x = 2; x < 252; x++)		//start from 2 pixels over
	{
		d = distances[x];
		e = 1.5*totalvariance;
		if ( d > average - e && d < average + e)
		{							// allow all pixels that are within 1.5 sigma of the average
			inbounds[x] == 1;
			inboundcount++;
			sum+=distances[x];		// count and add all the good pixels
		}
		else
			inbounds[x] == 0;
	}
	average = sum/inboundcount;		// calculate new average
	fprintf(o,"In bounds: %d/252\nNew Displacement Average: %d\n", inboundcount, average);

	fclose(f);
	fclose(o);

	return(0);
}
