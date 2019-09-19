.globl  lsearch_2
        #       %rsi: n
        #       %rdi: A[] first element
        #       %rdx: target
        #       %r9d: temp

lsearch_2:
        testl   %esi, %esi                      # if (n <= 0)			// if(n<= 0){
        jle     loopend                         # return -1;			// 	return -1
        movslq  %esi, %rax                      # rax = n			// }
        leaq    -4(%rdi,%rax,4), %rax           # rax = address of last element
        movl    (%rax), %r9d                    # int temp = A[n-1];		// int temp = A[n-1]
        movl    %edx, (%rax)                    #  				// A[n-1] = target
        cmpl    (%rdi), %edx                    # if A[0] == target		
        je      targetfound                     # target found
        movl    $1, %ecx                        # i = 1
loop:
        movl    %ecx, %r8d                      # start of while loop            //while(A[i]!=target){
        addq    $1, %rcx                        # i += 1			 //	i += 1;
        cmpl    %edx, -4(%rdi,%rcx,4)           # if (A[i] == target)		 //
        jne     loop                            # end of while loop jmp to start //}
restoretemp:
        movl    %r9d, (%rax)                    # 				 //A[n-1] = temp
        leal    -1(%rsi), %eax                  # set return value to n-1	 // if(i<(n-1)){
        cmpl    %r8d, %eax                      # if (i == n-1)			 // 	return(n-1);}
        jg      returnlastindex                 # jmp to last index check	 // else if (A[n-1] == target){
        cmpl    %edx, %r9d                      # if (A[n-1] == target)		 // 	return n-1;}
        jne     loopend                         # go return -1			 // else { return -1;}
        rep ret
returnlastindex:
        movl    %r8d, %eax                      # return (n-1)
        ret
targetfound:
        xorl    %r8d, %r8d                      # clear %r8d
        jmp     restoretemp                     # jmp to L4
loopend:
        movl    $-1, %eax                       # return -1
        ret
