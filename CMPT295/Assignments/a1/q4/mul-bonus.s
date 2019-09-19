	.globl times
times:
        mov %rdi, %r8   #store value of a into %r8
        mov %rsi, %r9   #store value of b into %r8
        mov $2, %rbx    #set up a dividor 2
        mov $0, %r10    #setup the result value into %r10
        cmp %r8, %r9    #compare a with b to see which is smaller
        jle bsmall              #use the smaller one to be dividend
        jmp asmall
        bsmall:
                mov %r9, %rax   #setup the division 
                loopb:
                        mov $0, %rdx
                        idiv %rbx
                        cmp $0, %rdx
                        je nextstepb
                        add %r8, %r10
                        nextstepb:
                                        add %r8, %r8
                                        cmp $0, %rax
                                        je loopend
                                        jmp loopb
        asmall:
                mov %r8, %rax   #setup the division 
                loopa:
                        mov $0, %rdx
                        idiv %rbx
                        cmp $0, %rdx
                        je nextstepa
                        add %r9, %r10
                        nextstepa:
                                        add %r9, %r9
                                        cmp $0, %rax
                                        je loopend
                                        jmp loopa

loopend:
        mov %r10, %rax
        ret

