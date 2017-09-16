%define AUTHOR_OFFSET 0
%define TITLE_OFFSET 21
%define SUBJECT_OFFSET 54
%define YEAR_OFFSET 68

	        SECTION .text   ; Code section.
	        global  bookcmp
	        extern  book1, book2 ; globals from sort_books.c

;;;   Subroutine begin

bookcmp:
	        push    edx
	        push    ebx
	        push    ecx
	        push    ebp
	        push    esp
	        push    esi
	        push    edi
	        mov     eax, 0
	        mov     ebx, 0
	        mov     ecx, 0
	        mov     edx, 0
	        mov     esi, 0
	        mov     edi, 0
	        mov     ebx, [book1] ; store location of first book
	        mov     ecx, [book2] ; store location of second book

year_compare:
	        xor     eax, eax
	        xor     esi, esi
	        xor     edi, edi
	        xor     edx, edx
	        mov     eax, [ebx + YEAR_OFFSET]; store location of year book 1
	        mov     esi, [ecx + YEAR_OFFSET]; store location of year book 2
	        cmp     eax, esi		; compare year
	        je 	title_compare	     	; if years are equal jump to title compare
		ja	book1_greater 		; if book1 has a lower year jump to book1_lower

book1_lower:
	        mov     eax, -1
	        jmp     end

book1_greater:
	        mov     eax, 1
	        jmp     end

title_compare:
		xor     eax, eax
	        xor     esi, esi
	        xor     edi, edi
	        xor     edx, edx
		xor 	ebp, ebp
		lea	edx, [ebx + TITLE_OFFSET] ; store the address of the first letter
=		lea 	ebp, [ecx + TITLE_OFFSET] ; store the address of the first letterompare_letters:
		mov     al, [edx]		  ; store the value at that address
	        mov     cl, [ebp]		  ; store the value at that address
		cmp     cl, al 		; compare them to each other
		jb	book1_greater
		ja	book1_lower
next_letter:
		cmp 	al, 0	; CHECK IUF ITS NULL
		je	actually_equal 		; if last character has been checked and is a match they are equal
		inc	edx
		inc 	ebp
		jmp 	compare_letters		; check next letter
actually_equal:
	        mov     eax, 0

end:
	        pop     edi
	        pop     esi
	        pop     esp
	        pop     ebp
	        pop     ecx
	        pop     ebx
	        pop     edx
		ret
;;;   Subroutine end