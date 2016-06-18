; rdrand64.asm provides 64-bit assembly implementations of functions which invoke RDRAND
; suitable for assembly with 64-bit MASM (ML64.EXE)
;
; Author: Stephen Higgins
; Blog: http://blog.viathefalcon.net/
; Twitter: @viathefalcon
;

PUBLIC rdrand_next, rdrand_uniform_ex
.CODE
	ALIGN 8

rdrand_next PROC FRAME
; bool rdrand_next(__deref_out unsigned* dest)
; ecx <= dest
	.endprolog

	db 00Fh, 0C7h, 0F0h	; Invoke RDRAND via its opcode [1], [2]
	jnc rdrand_err		; If no value is/was available, jump down
	mov [rcx], eax		; Move the random value from EAX into the destination address (received via RCX)
	mov eax, 1			; Set true into EAX
	ret					; Return with result in EAX

rdrand_err:
	mov eax, 0			; Set false into EAX
	ret					; Return with result in EAX
rdrand_next ENDP

rdrand_uniform_ex PROC FRAME
; uint64_t rdrand_uniform_ex(__in uint64_t lower, __in uint64_t upper)
; rcx = lower (bound; inclusive)
; rdx = upper (bound; exclusive)
	.endprolog

	db 048h, 00Fh, 0C7h, 0F0h		; Invoke RDRAND via its opcode [2]
	jnc epilogue

	; Get the range from which to select a number
	sub rdx, rcx
	dec rdx

	; At this point, the random value is in RAX and the range in RDX;
	; we regard the contents of RAX as the fractional part [3] of a 128-bit
	; unsigned fixed point number (where the integer part is 0) and the
	; contents of RDX as the integer part of a 128-bit fixed point number
	; (where the fractional part is 0).
	;
	; Because the top and bottom 64 bits, respectively, of our would-be 128-bit
	; inputs will always be zero we need only multiply the other 64 bits of each,
	; to obtain the middle 128 bits of the product. Conveniently, we have
	; just the instruction for this..
	mul rdx

	; The 128-bit fixed point product (integer:fraction) is given in RDX:RAX,
	; and by discarding the latter, we effectively truncate, to give us a
	; number n, 0 <= n < (upper - lower); adding lower gives us n, lower <= n < upper
	add rdx, rcx

epilogue:
	mov rax, rdx
	ret

rdrand_uniform_ex ENDP
END

; [1] Because we don't specify a REX prefix, the instruction's output is 32-bit
; [2] The destination register is specified by the final (MOD R/M) byte:
;	  F0 = C0 | 30, C0 = Register addressed to EAX, c.f. http://www.c-jump.com/CIS77/CPU/x86/X77_0060_mod_reg_r_m_byte.htm
; [3] x * 2^-64