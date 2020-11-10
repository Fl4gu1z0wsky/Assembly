;-------------------
;      ch02_04.asm
;-------------------

; extern "C" int IntegerMulDiv_(int a, int b, int* prod, int* quo, int* rem)

; Returns: 0 = error (divisor equals zero), 1 = success

	.code
IntegerMulDiv_ proc

; Make sure the divisior is not zero
	mov eax, edx					; eax = b
	or eax, eax						; logical OR sets status flags
	jz InvalidDivisor				; jump if b is zero

; Calculate product and save result
	imul eax, ecx					; eax = a * b
	mov [r8], eax					; save product

; Calculate quotient and remainder, save results
	mov r10d, edx					; r10d = b
	mov eax, ecx					; eax = a
	cdq								; edx:eax contains 64-bit dividend
	idiv r10d						; eax = quotient, edx = remainder

	mov [r9], eax					; save quotient
	mov rax, [rsp+40]				; rax = 'rem' (rsp [stack pointer] point to the top of
									; the stack while rbp [base pointer] point to the base)
	mov [rax], edx					; save remainder
	mov eax, 1						; set success return code

InvalidDivisor:
	ret

IntegerMulDiv_ endp
	end