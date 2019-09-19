	.globl sqrt
sqrt:
	mov $0, %rax   #
	mov $16384, %r8
loop:
	cmp $0, %r8
	jle end
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
end:
	ret
