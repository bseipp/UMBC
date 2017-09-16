; File: main.asm
;
; main program that exercises the prt_dec subroutine
;

%define STDIN 0
%define STDOUT 1
%define SYSCALL_EXIT  1
%define SYSCALL_READ  3
%define SYSCALL_WRITE 4


        SECTION .data                   ; initialized data section

lf:   	db  10            		; just a linefeed 

msg1:	db " there be boats "	
len1 equ $ - msg1

msg2: 	db " are how many pirates "
len2 equ $ - msg2

msg3:	db " are here "
len3 equ $ - msg3

        SECTION .text                   ; Code section.
        global  _start                  ; let loader see entry point
	extern	prt_dec

_start: 
	mov	ebx, 588
	mov	edx, 855
	mov	edi, 666
	mov	ebp, 777 


	push	dword 0x0F3A34
	call	prt_dec
	add	esp, 4
	call	prt_lf

	push	dword 0xFFFF0000
	call	prt_dec
	add	esp, 4
	call	prt_lf

	push	444
	call	prt_dec
	add	esp, 4
	call	prt_lf

	push	ebx
	call	prt_dec
	add	esp, 4
	call	prt_lf

	push	edx
	call	prt_dec
	add	esp, 4
	call	prt_lf

	push	edi
	call	prt_dec
	add	esp, 4
	call	prt_lf

	push	ebp
	call	prt_dec
	add	esp, 4
	call	prt_lf

	push	111
	call	prt_dec
	add	esp, 4

        mov     eax, SYSCALL_WRITE      ; write message
        mov     ebx, STDOUT
        mov     ecx, msg1
        mov     edx, len1
        int     080h
	
	push	555
	call	prt_dec
	add	esp, 4

        mov     eax, SYSCALL_WRITE      ; write message
        mov     ebx, STDOUT
        mov     ecx, msg3
        mov     edx, len3
        int     080h

	push	666
	call	prt_dec
	add	esp, 4
	call	prt_lf

	push	777
	call	prt_dec
	add	esp, 4

        mov     eax, SYSCALL_WRITE      ; write message
        mov     ebx, STDOUT
        mov     ecx, msg2
        mov     edx, len2
        int     080h
	
	push	444
	call	prt_dec
	add	esp, 4

        mov     eax, SYSCALL_WRITE      ; write message
        mov     ebx, STDOUT
        mov     ecx, msg3
        mov     edx, len3
        int     080h

	push	333
	call	prt_dec
	add	esp, 4
	call	prt_lf


        ; final exit
        ;
exit:   mov     EAX, SYSCALL_EXIT       ; exit function
        mov     EBX, 0                  ; exit code, 0=normal
        int     080h                    ; ask kernel to take over



	; A subroutine to print a LF, all registers are preserved
prt_lf:
	push	eax
	push	ebx
	push	ecx
	push	edx

        mov     eax, SYSCALL_WRITE      ; write message
        mov     ebx, STDOUT
        mov     ecx, lf
        mov     edx, 1			; LF is a single character
        int     080h

	pop	edx
	pop	ecx
	pop	ebx
	pop	eax
	ret

