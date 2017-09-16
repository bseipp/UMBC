%define STDIN 0
%define STDOUT 1
%define SYSCALL_EXIT  1
%define SYSCALL_READ  3
%define SYSCALL_WRITE 4
%define BUFLEN 256

	    SECTION .bss			; uninitialized data section
base_2_str: resb 	BUFLEN			; stores backwards base 2 number
base_10_str:resb 	BUFLEN			; base 10 number will be stored here
rlen:	    resb 	4             		

	    SECTION 	.text
	    global      prt_dec

	;;  Begin subroutine

prt_dec:
	    push	eax
	    push	ebx
	    push	ecx
	    push	edx
	    push	esi
	    push	edi
	    xor		ecx, ecx 		; zero out ecx
	    mov 	eax, [esp + 28] 	; store the decimal number 4 bytes each for each push, plus the eip
	    mov 	esi, base_2_str         ; point esi to the backwards string buffer
	    mov 	edi, base_10_str    	; point edi to the new buffer
	    mov 	ebx, 10	    		; put 10 into ebx

convert_to_base_10:
	    xor 	edx, edx          	; reset edx
	    div 	ebx         		; divide the number by 10
	    add 	dl, '0'			; convert remainder to character ascii code
	    mov 	[esi], dl	      	; move char to output buffer
	    inc 	esi         		; move to next spot on output buffer
	    inc 	ecx         		; keep track of how many chars are added
	    test 	eax, eax          	; check if eax is empty, and there is more to divide into
	    jnz 	convert_to_base_10	; continue loop if eax is not 0
	    mov		[rlen], ecx		; store the number of characters into the value
	
print_char:
	    dec 	esi			; point to last/previous digit
	    mov 	al, [esi]		
	    mov 	[edi], al       	
	    inc 	edi         		
	    dec 	ecx         		
	    jnz 	print_char

print_to_screen:
	    mov		eax, SYSCALL_WRITE
	    mov 	ebx, STDOUT
	    mov 	ecx, base_10_str
	    mov 	edx, [rlen]
	    int 	080h

pop_end:
	    pop 	edx         		; return values to original register edx
	    pop 	esi			; s/a esi
	    pop 	edi			; s/a edi
	    pop 	ebx			; s/a ebx
	    pop 	ecx			; s/a ecx
	    pop     	eax			; s/a eax
	    ret					; return call

	;;  End subroutine