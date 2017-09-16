;; Brian Seipp
	;; Assembly 313 Park 2016
	
	  SECTION .data		

label1:	   db "Enter string: "	
len1:	   equ $-label1		

label2:	   db "Original: "	
len2:	   equ $-label2		

label3:	   db "Convert:  "	
len3:	   equ $-label3

newLine:	db 10 	
len5:	   equ $-newLine

	   SECTION .bss	
buf:	   resb 256
newstr:	   resb 256		
rlen:	   resb 4		


	   SECTION .text
	   global  _start

_start:
	   nop		
start:			

	;;  print label1 to screen for user input
	   mov     eax, 4 
	   mov     ebx, 1	   
	   mov     ecx, label1	   
	   mov     edx, len1	   
	   int     080h		   

	;;  scan input
	   mov     eax, 3
	   mov     ebx, 0	  
	   mov     ecx, buf	  
	   mov     edx, 256	  
	   int     080h
	   mov     [rlen], eax
initialize:
	   mov     ecx, [rlen] 
	   mov     esi, buf    
	   mov     edi, newstr 

top:
	   mov     al, [esi] 
	   inc     esi	  
	   cmp     al, ' '
	   je      cont
	   cmp     al, '='
	   je      cont
	   cmp     al, '1'
	   je      cont
	   cmp     al, '+'
	   je      cont
	   cmp     al, '!'
	   je      cont
	   cmp     al, '?'
	   je	   cont
	cmp al, '$'
	je cont
	   cmp     al, 'a'	; < a
	   jb      uppercasewrap
	   cmp     al, 'm'	; > z
	   ja      lowercaseshift
	   add     al, 13	; shift 13

cont:
	   mov     [edi], al 
	   inc     edi	  
	   dec     ecx	  
	   jnz     top


uppercasewrap:
	   cmp    ecx, 0
	   jz     end
	   cmp    al, 'M'
	   jb     uppercaseshift
	   cmp    ecx, 0
	   jz     end
	   sub    al, 13
	   mov    [edi], al
	   inc    edi
	   dec    ecx
	   jnz    top

uppercaseshift:
	   cmp    ecx, 0
	   jz     end
	   add    al, 13
	   mov    [edi], al
	   inc    edi
	   dec    ecx
	   jnz    top

lowercaseshift:
	   cmp    ecx, 0
	   jz     end
	   sub    al, 13
	   mov    [edi], al
	   inc    edi
	   dec    ecx
	   jnz    top

end:
	;;  print the user input back to them for confirmation
	   mov     eax, 4 ; label
	   mov     ebx, 1
	   mov     ecx, label2
	   mov     edx, len2
	   int     080h

	   mov     eax, 4 ; value
	   mov     ebx, 1
	   mov     ecx, buf
	   mov     edx, [rlen]
	   int     080h

	;;  print translated string
	   mov     eax, 4 ; label
	   mov     ebx, 1
	   mov     ecx, label3
	   mov     edx, len3
	   int     080h

           mov     eax, 4 ; value
	   mov     ebx, 1
	   mov     ecx, newstr
	   mov     edx, [rlen]
	;; 	   mov     dl, 0Dh
	   int     080h

	;; print new line
	
	   mov     eax, 4 ; write message
	   mov     ebx, 1
	   mov     ecx, newLine
	   mov     edx, len5
	   int     080h
	
exit:	   mov     eax, 1 
	   mov     ebx, 0	     
	   int     080h	  