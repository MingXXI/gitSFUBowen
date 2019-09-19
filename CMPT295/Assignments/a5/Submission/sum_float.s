.globl sum_float

sum_float:
        push    %rbp                            # push %rbp to stack
        xorps   %xmm0, %xmm0                    # total <- 0.0
        leaq    -8(%rsp), %rsp                  # move down %rsp to a empty stack
        movq    %rsp, %rdx                      # save the first empty stack addr to %rdx
        movq    %rdx, %r8                       # save the first empty stack addr to %r8
        movq    %rdi, %r9                       # save the F base ptr to %r9
        movq    $0, (%rdx)                      # clear the value %rdx points to
        movq    %rsi, %rcx                      # save n into %rcx
        decq    %rcx                            # set the loop counter to n-1
        leaq    (%rdi, %rsi, 4), %rbp           # set %rbp be the end of F

loop:   
        cmpq    $1, %rcx                        # check if add enough times
        jl      endloop                         # jump to end the loop
        cmpq    %rdx, %rsp                      # check if Q is empty
        je      dequeueFx                       # deque from F if Q empty
        cmpq    %rdi, %rbp                      # check if F empty
        je      dequeueQx                       # deque from Q if F empty
        movss   (%rdi), %xmm1                   # move the first element in F to %xmm1
        movss   (%rdx), %xmm2                   # move the first element in Q to %xmm2
        ucomiss %xmm1, %xmm2                    # compare %xmm1 and %xmm2
        jae     dequeueFx                       # deque from F if %xmm1 smaller
        movss   (%rdx), %xmm3                   # dequeue from Q to x
        leaq    -8(%rdx), %rdx                  # set the head(Q) to next element in Q
        jmp     findy

dequeueFx:                                      # deque head(F) to x
        movss   (%rdi), %xmm3
        leaq    4(%rdi), %rdi                   # set the head of F to next element
        jmp     findy
dequeueQx:                                      # deque head(Q) to x
        movss   (%rdx), %xmm3
        leaq    -8(%rdx), %rdx                  # set the head of Q to next element
        jmp     findy


findy:
        cmpq    %rdx, %rsp                      # check if Q empty
        je      dequeueFy                       # deque from F if Q empty
        cmpq    %rdi, %rbp                      # check if F empty
        je      dequeueQy                       # deque from Q if F empty
        movss   (%rdi), %xmm1                   # move the first element in F to %xmm1
        movss   (%rdx), %xmm2                   # move the first element in Q to %xmm2
        ucomiss %xmm1, %xmm2                    # compare %xmm1 and %xmm2
        jae     dequeueFy                       # deque from F if %xmm1 smaller
        movss   (%rdx), %xmm4                   # dequeue from Q to y
        leaq    -8(%rdx), %rdx                  # set the head(Q) to next element in Q
        jmp     xplusy

dequeueFy:                                      # deque head(F) to y
        movss   (%rdi), %xmm4
        leaq    4(%rdi), %rdi                   # set the head of F to next element
        jmp     xplusy
dequeueQy:                                      # deque head(Q) to x
        movss   (%rdx), %xmm4
        leaq    -8(%rdx), %rdx                  # set the head of Q to next element
        jmp     xplusy

xplusy:
        addss   %xmm3, %xmm4                    # y = x + y
        movss   %xmm4, %xmm0                    # total <- x+y
        movss   %xmm0, (%rsp)                   # queue the x+y into Q
        leaq    -8(%rsp), %rsp                  # move down %rsp to next empty stack                 
        decq    %rcx                            # count down loop counter
        jmp     loop                            # loop again


endloop:
        xorps   %xmm0, %xmm0                    # clear %xmm0
        movss   (%rdx), %xmm0                   # move head(Q) into %xmm0
        leaq    -8(%rdx), %rdx                  # set head(Q) to next element
sumloop:
        cmpq    %rsp, %rdx                      # check if Q is empty
        je      end                             # if Q is empty, end
        addss   (%rdx), %xmm0                   # add every elements in Q to %xmm0
        leaq    -8(%rdx), %rdx                  # set head(Q) to next element
        jmp     sumloop                         # sumloop again
end:
        movq    %r8, %rsp                       # restore original stack pointer
        movq    %r9, %rdi                       # restore original F[n] pointer
        leaq    8(%rsp), %rsp                   # move the stack pointer to pop %rbp
        pop     %rbp                            
        ret                                     # return

