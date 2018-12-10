makeall: transformaciones.o programa

transformaciones.o: transformaciones.asm
	nasm -f elf64 transformaciones.asm

programa: transformaciones.o
	gcc -o programa transformaciones.o main.c
