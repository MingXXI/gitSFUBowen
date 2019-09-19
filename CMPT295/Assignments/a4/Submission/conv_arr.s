	.globl conv_arr
conv_arr:
	pushq %r12
	pushq %r13
	pushq %r14
	pushq %r15
	movq %rsi, %r12		# set %r12 as n
	addq %rcx, %r12		# %r12 <- n+m
	subq $2, %r12		# %r12 <- n+m-2
	movq $0, %r13		# set %r13 as loop counter i
loop:
	cmpq %r12, %r13		# test the loop constrain
	jg loopend		
#calculate ladj:	
	pushq %rdi			#
	pushq %rsi			#
 	pushq %rdx			#
	pushq %rcx			#
	pushq %r8			# push values in register onto stack
	incq %r13			# i = i +1
	movq %r13, %rdi		# move (i+1) to %rdi for calling min
	movq %rcx, %rsi		# move m to %rsi for calling min
	call min			# call min function
	popq %r8			# 
	popq %rcx			#
	popq %rdx			#
	popq %rsi			#
	popq %rdi			# pop values saved previously back to registers
	movq %rax, %r14		# save ladj to %r14	
#calculate radj:
	pushq %rdi			#
	pushq %rsi 			#
 	pushq %rdx			#
	pushq %rcx			#
	pushq %r8			# push values in register onto stack
	addq %rcx, %rsi 	# m+n
	subq %r13, %rsi 	# m+n-(i+1)
	movq %rcx, %rdi		# move m to %rdi for calling min
	call min			# call min function
	popq %r8			#
	popq %rcx			#
	popq %rdx			#
	popq %rsi 			#
	popq %rdi			# pop values saved previously back to registers
	pushq %rcx			# push values in %rcx onto stack
	subq %rax, %rcx		# m - min(m+n-(i+1), m)
	movq %rcx, %r15		# save radj to %r15
	popq %rcx			# pop %rcx from stack
#call conv:
	pushq %r13			#
	pushq %rdi		 	#
	pushq %rsi 			#
 	pushq %rdx			#
	pushq %rcx			#
	pushq %r8			# push values in register onto stack
	subq %r14, %r13		# i+1-ladj
	addq %r13, %rdi		# x+(i+1-ladj)
	addq %r15, %rdx		# h+radj
	movq %rdx, %rsi 	# setup second argument in conv function
	movq %r14, %rdx		# move ladj into %rdx
	subq %r15, %rdx		# ladj-radj
	call conv 			# call conv function
	popq %r8			#
	popq %rcx			#
	popq %rdx			#
	popq %rsi 			#
	popq %rdi			#
	popq %r13			# pop values saved previously back to registers
	movb %al, (%r8)		# save the result from conv into (%r8)
	incq %r8			# increase %r8 to next index of array
	jmp loop 			# jump to the start of the loop
loopend:
	popq %r15			#
	popq %r14			#
	popq %r13			#
	popq %r12			# pop value from stack into previous registers
	ret 				# return
