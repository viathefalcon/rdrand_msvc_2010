; rdrand64.asm Implements a single function, rdrand, which invokes
; the RDRAND instruction and returns the result; suitable for
; assembly with 64-bit MASM (ML64.EXE)
;
; Although this is 64-bit code, we refer to EAX rather than
; RAX, because the output is still a 32-bit value
;
; Author: Stephen Higgins <sjh@viathefalcon.net>
; Blog: http://blog.viathefalcon.net/
; Twitter: @viathefalcon
;

PUBLIC rdrandx64
.CODE
	ALIGN 8
rdrandx64 PROC FRAME
; bool rdrandx64(__deref_out unsigned* dest)
; ecx <= dest
	.endprolog

	db 00Fh, 0C7h, 0F0h	; Invoke RDRAND via its opcode
	jnc rdrand_err		; If no value is/was available, jump down
	mov [rcx], eax		; Move the random value from EAX into the destination address (received via RCX)
	mov eax, 1			; Set true into EAX
	ret					; Return with result in EAX

rdrand_err:
	mov eax, 0			; Set false into EAX
	ret					; Return with result in EAX

	ALIGN 8
rdrandx64 ENDP
END
