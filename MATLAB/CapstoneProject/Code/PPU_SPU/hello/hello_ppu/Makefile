#Target

hello_ppu: main.o
	ppu-gcc -m32 -o hello_ppu hello_ppu.c  -lspe2
main.o: hello_ppu.c
	gcc -c hello_ppu.c -o main.o
