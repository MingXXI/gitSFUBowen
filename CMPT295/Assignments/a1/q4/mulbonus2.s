	.globl times
times:
	cmp %rdi, %rsi	#compare a with b to see which is smaller
	mov $1, %r9		#setup the counter of times of doubling

	jle bsmall		#use the smaller one to be dividend
	jmp asmall

bsmall:
	mov %rdi, %r8	#store the initial value of larger value to r8
	mov %rsi, %r10	#setup the smaller multiplier to r10
	mov %rdi, %r11
	jmp loop
asmall:
	mov %rsi, %r8	#
	mov %rdi, %r10	#
	mov %rsi, %r11
	jmp loop

loop:
	cmp %r9,%r10
	jle loopend
	add %r8, %r8
	add %r9, %r9
	jmp loop

loopend:
	sub %r10, %r9
	substructback:
		cmp $0, %r9
		jle done
		sub %r11, %r8
		dec %r9
		jmp substructback
done:
	mov %r8, %rax
	ret


