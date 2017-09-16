; File: bookcmp.asm
;
;Defines the bookcmp subroutine for use by the sort algorithm in sort_books.c
;
%define AUTHOR_OFFSET 0
%define TITLE_OFFSET 21
%define SUBJECT_OFFSET 54
%define YEAR_OFFSET 68
	

        SECTION .text                   ; Code section.
        global  bookcmp                 ; let loader see entry point
	extern	book1, book2

bookcmp: 
	push	ebp			; push registers we want to use
	mov	esp, ebp		; get the pointer to the first book
	mov 	eax, [esp + YEAR_OFFSET]; fetch book 1's year field

	mov 	esp, ebp + 76		; get the pointer to the second book
	sub 	eax, [esp + YEAR_OFFSET]; compare to book 2's year
	jnz	allDone			; If they're different, we're done
					; with comparisons

cmpTitles:				; Fall through to here if years same
	;; Following could also be done using "lea" instruction
	mov	esp, ebp		
	mov	eax, [esp + TITLE_OFFSET]

	mov	ecx, ebp + 76		
	sub	eax, [ecx + TITLE_OFFSET]
	
L1:	mov	al, [ecx]		; Fetch next char of book1's title
	sub	al, [esi]		; and compare it to matching char in
					; book 2
	jne	titleCmpDone		; If we find a difference, we are done
					; (note this also works if one string
					; or other at NULL)

	;; So far, all chars equal; see if we are at end (i.e., check for NULL)
	cmp	byte [edi], 0
	je	titleCmpDone
	inc	edi
	inc	esi
	jmp	L1

titleCmpDone:
	movsx	eax, al			; need to convert 8-bit to full 32-bit

allDone:				; Clean up and finish
	;; Note that eax already has an appropriate value <0, =0, or >0
	pop	edx
	pop	ecx
	pop	esi
	pop	edi
	ret
