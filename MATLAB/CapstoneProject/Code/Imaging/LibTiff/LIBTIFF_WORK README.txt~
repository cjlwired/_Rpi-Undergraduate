libtiff_work

This directory contains LIBTIFF (thank you, SGI) and four C files. The only C file that matters is "d-tiff2pgm.c" as it is the complete from-scratch conversion program source. The rest are working files of varying completion and usefulness (not much, altogether), included for completeness. Nothing else in the LIBTIFF directory ("tiff-3.8.2") have been changed. LIBTIFF is available from libtiff.org under a free attribution license contained near the top of "d-tiff2pgm.c".

d-tiff2pgm is used as follows:

> d-tiff2pgm [filename.tiff]

It will either return an error if the tiff isn't 8-bit, single-channel grayscale, the file is missing, etc., or it will output filename.pgm and exit.

NOTE: d-tiff2pgm compiles but does not link on the PS3. It has unresolved dependency issues, missing major commands which should be contained and controlled by the #included .h files. I suspect this is a problem with the IDE (namely, that I am unfamiliar with gcc and haven't pointed it at the right directories).
