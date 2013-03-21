#include "tiffio.h"
#include <stdio.h>
// Endian-ness is specified in-file; defaults to CPU preference if missing

int main(int argc, char* argv[]) 
{
    	// Quit if parameter missing
    if(argc == 1) { printf("Correct use: ", argv[0], "filename\n"); return 0; }
    
    	// Open the parameter for reading
    TIFF* imagehandle = TIFFOpen(argv[1], "r");
    if(!imagehandle) { printf("Couldn't open ", argv[1], '\n'); return 0; }
    
        // Format check
    int samplesperpixel, bitspersample;
    TIFFGetField(in, TIFFTAG_SAMPLESPERPIXEL, &samplesperpixel);
    TIFFGetField(in, TIFFTAG_BITSPERSAMPLE, &bitspersample);
    if (samplesperpixel != 1 && bitspersample !=8) {
    printf("8-bit greyscale images only.\n"); return 0;}
    // We can discard the variables in this codeblock now.

        //If we get this far, create/open an output file
    FILE *outfile;
    outfile = fopen(argv[1] + ".pgm", "w"); // e.g. foo.tiff.pgm
    fprintf(outfile, "P5\n256\n256\n255\n"); // PGM formatting: 8-bit, 256x256
