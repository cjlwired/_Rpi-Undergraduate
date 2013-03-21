
#include <math.h>
#include <stdio.h>
#include <stdlib.h>



int main (int argc, char ** argv)
{

	FILE *f;
	FILE *o;
	char r[256];
	char t[256];
	int m[255][255];
	int x = 0; 
	int y = 0;
	int z = 0;
	int k;

	if (argc != 4)
	{
		printf("Not enough arguments!\n");
		exit(2);
	}

	k = atoi(argv[3]);

	f = fopen(argv[1],"r");	// open image
	if (f == NULL)				// check for existence of file
		exit(1);



	for (y = 0; y < 255; y++)	// read all of the integers into a matrix
	{
		for (x = 0; x < 255; x++)
		{

			fscanf(f,"%s",t);
			m[y][x] = atoi(t)/k;  // change this to atoi(t)/128 if the input is not already binary
		}
	}

	o = fopen(argv[2],"w");	// open output file

	for(y = 0; y < 255; y++)
	{
		for(x = 0; x < 255; x++)
		{
			fprintf(o,"%d ",m[y][x]);
		}
		fprintf(o,"\n");
	}


	fclose(f);
	fclose(o);

	return(0);
}
