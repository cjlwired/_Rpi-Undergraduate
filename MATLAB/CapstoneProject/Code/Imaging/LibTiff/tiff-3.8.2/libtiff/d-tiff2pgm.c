#include "tiffio.h"
#include <stdio.h>
// Endian-ness is specified in-file; defaults to CPU preference if missing

// Compiles, but does not link. "undefined reference to..." tiffopen,
// tiffgetfield, tiffreadscanline, etc.

int main(int argc, char* argv[]) 
{
    	// Quit if parameter missing
    if(argc == 1) { printf("Correct use: ", argv[0], "filename\n"); return 0; }
    
    	// Open the parameter for reading
    TIFF* imagehandle = TIFFOpen(argv[1], "r"); // Quit if this fails
    if(!imagehandle) { printf("Couldn't open ", argv[1], '\n'); return 0; }
    
        // Format check
    uint32 samplesperpixel, bitspersample;
    TIFFGetField(imagehandle, TIFFTAG_SAMPLESPERPIXEL, &samplesperpixel);
    TIFFGetField(imagehandle, TIFFTAG_BITSPERSAMPLE, &bitspersample);
    if (samplesperpixel != 1 && bitspersample !=8) {
    printf("8-bit greyscale images only.\n"); return 0;}
    // We can discard the variables in this codeblock now.

        // If we get this far, create/open an output file
    FILE *outfile;
    char* infilename = (char *)calloc(strlen(argv[1]) + 5, sizeof(char));
    strcat(infilename, argv[1]); 
    strcat(infilename, ".pgm");
    outfile = fopen(infilename, "w"); // e.g. foo.tiff.pgm
    fprintf(outfile, "P5\n256\n256\n255\n"); // PGM formatting: 8-bit, 256x256
    
    // Read TIFF pixels, output to file
    uint32 row = 0;
    tsample_t sample; // unused but neccessary; marks multiplane TIFFs
    unsigned char* inbuf = (unsigned char *)_TIFFmalloc(TIFFScanlineSize(imagehandle));
    while(TIFFReadScanline(imagehandle, inbuf, row, 0) == 1 && row < 256)
    {
        // For each buffer element, fprintf to outfile 
        int k;
        for(k = 0; k < 255; k++)
        {
            int whatisaunary = inbuf[k];
            fprintf(outfile, whatisaunary);    // the hell is a unary?
            fprintf(outfile, "\n");
        }
        // Newline after each scanline
        fprintf(outfile, "\n");
    }
    
    return 0;
}
