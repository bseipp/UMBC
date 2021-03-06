%define STDIN 0
	%define STDOUT 1
	%define SYSCALL_EXIT  1
	%define SYSCALL_READ  3
	%define SYSCALL_WRITE 4
	%define BUFLEN 256


	        SECTION .data	; initialized data section

msg1:	   db "Enter string: "	; user prompt
len1:	   equ $-msg1		; length of first message

msg2:	   db "Original: "	; original string label
len2:	   equ $-msg2		; length of second message

msg3:	   db "Convert:  "	; converted string label
len3:	   equ $-msg3

msg4:	   db 10, "Read error", 10 ; error message
len4:	   equ $-msg4

msg5:	   db 10, "Error: unknown escape sequence", 10 ; unknown escape error (not sure this works)
len5:	   equ $-msg5

msg6:	   db 10, "Error: octal value overflow!", 10 ; overflow error
len6:	   equ $-msg6

	;;  Declare the array using mappings.
mappings:	 db 7, 8, -1, -1, -1, 12, -1, -1, -1, -1, -1, -1, -1, 10, -1, -1, -1, 13, -1, 9, -1, 11, -1, -1, -1, -1


	        SECTION .bss	; uninitialized data section
buf:	    	resb BUFLEN		; buffer for read
newstr:	 	resb BUFLEN		; converted string
rlen:	   	resb 4		; length


	        SECTION .text	; Code section.
	        global  _start	; let loader see entry point

_start:	 nop			; Entry point.
start:				; address for gdb

	;;  prompt user for input
	;;
	        mov     eax, SYSCALL_WRITE ; write function
	        mov     ebx, STDOUT	   ; Arg1: file descriptor
	        mov     ecx, msg1	   ; Arg2: addr of message
	        mov     edx, len1	   ; Arg3: length of message
	        int     080h		   ; ask kernel to write

	;;  read user input
	;;
	        mov     eax, SYSCALL_READ ; read function
	        mov     ebx, STDIN	  ; Arg 1: file descriptor
	        mov     ecx, buf	  ; Arg 2: address of buffer
	        mov     edx, BUFLEN	  ; Arg 3: buffer length
	        dec     edx		  ; make sure the buffer length is 1 less than BUFLEN
	        mov     [ecx + edx], byte 0 ; null terminate the read buffer


	        int     080h

	;;  error check
	;;
	        mov     [rlen], eax ; save length of string read
	        cmp     eax, 0	    ; check if any chars read
	        jg      read_OK	    ; >0 chars read = OK
	        mov     eax, SYSCALL_WRITE ; ow print error mesg
	        mov     ebx, STDOUT
	        mov     ecx, msg4
	        mov     edx, len4
	        int     080h
	        jmp     exit	; skip over rest
read_OK:


	;;  Loop for iterating over string

L1_init:
	        mov     esi, buf ; point to start of buffer
	        mov     edi, newstr ; point to start of new string

L1_top:
	        mov     al, [esi] ; get a character
	        inc     esi	  ; point to the next character
	        cmp     al, '\'	  ; is current char a backslash?
	        je      escapectrl ; if so, run the subroutine
	        jmp     L1_cont	   ; if not, jump to L1_cont and add the char

escapectrl:
	        call    handle_ESC ; run subroutine
	        inc     edi
	        cmp     [esi], byte 0
	        je      L1_end
	        jmp     L1_top

L1_cont:
	        mov     [edi], al ; store char in new string
	        inc     edi	  ; update dest pointer
	        cmp     [esi], byte 0 ; if not null, keep looping
	        je      L1_end	      ; end loop if null
	        jmp     L1_top	      ; loop if there are more chars



L1_end:


	;;  print out user input for feedback
	;;
	        mov     eax, SYSCALL_WRITE ; write message
	        mov     ebx, STDOUT
	        mov     ecx, msg2
	        mov     edx, len2
	        int     080h

	        mov     eax, SYSCALL_WRITE ; write user input
	        mov     ebx, STDOUT
	        mov     ecx, buf
	        mov     edx, [rlen]
	        int     080h

	;;  print out converted string
	;;
	        mov     eax, SYSCALL_WRITE ; wri message
	        mov     ebx, STDOUT
	        mov     ecx, msg3
	        mov     edx, len3
	        int     080h

	        mov     eax, SYSCALL_WRITE ; write out string
	        mov     ebx, STDOUT
	        mov     ecx, newstr
	        mov     edx, [rlen]
	        int     080h


	;;  final exit
	;;
exit:	   mov     eax, SYSCALL_EXIT ; exit function
	        mov     ebx, 0	     ; exit code, 0=normal
	        int     080h	     ; ask kernel to take over

	;;  Subroutine begins here.

handle_ESC:

	        mov     bl, [esi] ; take a copy of the current char
	        inc     esi	  ; point to the next char

	        cmp     bl, '7'	; is it above 7?
	        ja      lowercase ; if so, skip octal check

	        cmp     bl, '0'	; is it below zero?
	        jb      lowercase ; if so, skip octal check

lowercase:
	        cmp     bl, 'a'	; is it a?
	        jb      slashprint ; jump out if it's below a
	        cmp     bl, 'z'	   ; is it z?
	        ja      slashprint ; jump out if it's above z
		movzx   ecx, bl	      ; move the char into ecx for indexing
		mov     ebx, mappings ; point to the mappings array
	        sub     ecx, 'a'      ; convert the lower case letter to decimal
	        mov     al, [ebx + ecx]	; indexed addressing done here
	        mov     [edi], al	; store converted char in write buffer
	        ret

slashprint:
	        cmp     bl, '\'	; is it another slash?
	        jne     errormsg ; jump and print an error message
	        mov     [edi], byte '\'	; add a space
	        ret

errormsg:
	        inc     esi	; skip over the character after the slash


done:
	        ret