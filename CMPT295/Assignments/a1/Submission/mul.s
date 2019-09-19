	.globl times
times:
	mov $0, %rax      
	mov $0, %r8
loop:	
		cmp %r8, %rsi
		jle loopend
		add %rdi, %rax
		inc %r8
		jmp loop
loopend:
		ret

