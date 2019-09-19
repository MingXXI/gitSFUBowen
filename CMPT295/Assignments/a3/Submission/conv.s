        .globl conv
conv:
        leaq -1(%rdi,%rdx), %rdi
        movq %rdx, %r10
        movl $0, %edx
        movb $0, %al

mainloop:
        cmpq $0, %r10
        jle done
        movsx (%rsi), %r9w
        movsx (%rdi), %r8w
        imulw %r9w, %r8w
        movb %r8b, %r9b
        movsx %r9b, %r9w
        cmpw %r9w, %r8w
        je mulsuccess
        mov $1, %edx
mulsuccess:
        addb %r8b, %al
        jno addsuccess
        mov $1, %edx
addsuccess:
        incq %rsi
        decq %rdi
        decq %r10
        jmp mainloop
done:
        ret