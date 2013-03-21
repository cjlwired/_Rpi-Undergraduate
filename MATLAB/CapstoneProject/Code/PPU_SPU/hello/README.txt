Paul Ireifej
PPU / SPU Information Exchange code

"hello.c" simulates the convolution code if it were to be split up into
4 quadrants of 129 x 129 matrices. This calls 4 SPEs, which run the convolution
algorithm on a randomly generated 129 by 129 2-dimensional array, and then returns.

"hello_temp.c" is a test for information exchange. Using advice that William Chung
at IBM offered to me, I attempted to pass an array to a single SPE. This does not
work, but has good code with regards to aligning an argument appropriately.

"hello_ppu" is a directory that contains general PPE code. It calls just one SPE,
but is a good start to PPU/SPU programming because it highlights each step for
a single SPE, thereby allowing you to learn everything in a simple and straightforward 
manner.

"hello_spu" is the code that is to be run a single SPE (or as many as you want).

I hope you find the code useful, and the comments beneficial. I advise you to
use this code as a starting point because it is the result of 3 months of 
research. 

Also, the Makefiles in each directory are difficult to put together
as they are not explained clearly in the IBM tutorials. Please use these to your
advantage because using these, the code compiles just fine.

Good luck! 
Paul Ireifej
ireifp@rpi.edu <-- e-mail me with questions anytime!!! :-)