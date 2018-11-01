section .rodata ; read only data section

	msg db "Hello, world!",0x0a ; String to be displayed

section .text ; code section

global _start ; extern symbol

_start: ; _start is entrypoint
	mov rax, 1 ; syscall number of write
	mov rdi, 1 ; fd 1 = stdout
	mov rsi, msg ; pointer to string to be displayed
	mov rdx, 14 ; bytes to be written
	syscall ; trigger kernel mode

	mov rax, 60 ; exit sycall number
	mov rdi, 0 ; exit 0 (success)
	syscall ; trigger kernel mode
