	.globl mystery
mystery:
	movl	$0, %eax
	leaq	(%rdi, %rsi), %rcx

loop:
	cmpq	%rdi, %rcx
	jle	endl
	decq	%rcx
	cmpb	$0x6f, (%rcx)
	jne	loop
	incl	%eax
	jmp	loop

endl:
	ret
