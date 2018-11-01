all:
	nasm -f elf64 hello.asm
	ld -o hello hello.o
	ld -o hello-strip hello.o --strip-all

clean:
	rm hello hello.o hello-strip
