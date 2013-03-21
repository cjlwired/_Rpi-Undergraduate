#Target

FILE = hello
FILEC = hello.c
FILEO = hello.o

$(FILE): main.o
	ppu-gcc -W -Wall -Winline -I. -I -O3 -c $(FILEC)
	ppu-gcc -o $(FILE) $(FILEO)  ./hello_spu/hello_spu.a -lspe2

main.o: $(FILEC)
	gcc -c $(FILEC) -o main.o -lspe2 -I /usr/lib/gcc/spu/4.1.1/include
