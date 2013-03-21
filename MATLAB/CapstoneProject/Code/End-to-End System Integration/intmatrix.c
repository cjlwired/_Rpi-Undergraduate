#include <math.h>
#include <stdio.h>
#include <stdlib.h>



int main (int argc, char ** argv)
{
	FILE *f;
	FILE *o;
	char r[256];
	char t[256];
	int distances[255];
	int x = 0; 
	int y = 0;



	if( argc != 3)
	{
		printf("Not enough arguments!\n");
		exit(1);
	}


	f = fopen(argv[1],"r");	// open image
	if (f == NULL)				// check for existence of file
		exit(1);

	fgets(t,255,f);				// trash the first 3 lines and 1st number
	fgets(t,255,f);
	fgets(t,255,f);
	fscanf(f,"%s",t);

	printf("hey\n");

	o = fopen(argv[2],"w");	// open output file

	for (y = 0; y < 255; y++)	// read all of the integers into a matrix
	{
		for (x = 0; x < 255; x++)
		{

			fscanf(f,"%s",t);
			fprintf(o,"%s ",t);
		}
		fprintf(o,"\n");
	}
	printf("hey2\n");
	fclose(f);
	fclose(o);

return 0;


}