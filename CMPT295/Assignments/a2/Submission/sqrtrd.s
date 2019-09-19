	.globl sqrt
sqrt:
	mov $0, %rax   #
	mov $16384, %r8
loop:
	cmp $0, %r8
	jle rounding
	add %r8, %rax
	mov %rax, %r9
	imul %r9, %r9 
	cmp %r9, %rdi
	jl changeback
	jmp nextbit
	changeback:
		sub %r8,%rax
	nextbit:
		shr $1, %r8
	jmp loop
rounding:
	mov %rax, %r10
	mov %rax, %r9	
	add $1, %r10
	imul %r9, %r9
	imul %r10, %r10
	sub %rdi, %r10
	sub %r10, %rdi
	cmp %rdi, %r9
	jle upper
	jmp end	
	upper:
		add $1, %rax
	add %r10, %rdi
end:
	ret
