
hello_spu: main.o
	spu-gcc -o hello_spu hello_spu.c -Wall
	ppu-embedspu -m64 hello_spu hello_spu hello_spu-embed64.o
	ppu-ar -qcs hello_spu.a hello_spu-embed64.o

main.o: hello_spu.c
	gcc -c hello_spu.c -o main.o
