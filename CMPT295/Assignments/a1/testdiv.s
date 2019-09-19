.globl times
times:
	mov $0, %edx
	mov $9, %eax
	mov $3, %esi
	idiv %esi
	ret