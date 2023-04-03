

;
; file: mul.asm

;
; Using Linux and gcc:
; nasm -f elf mul.asm
; gcc -o mul mul.o -m32 driver.c asm_io.o
;


%include "asm_io.inc"
;
; initialized data is put in the .data segment
;
segment .data
;
; These labels refer to strings used for output
;

;
; uninitialized data is put in the .bss segment
;
segment .bss
;
; These labels refer to double words used to store the inputs
;
;Parameters:
;	float a at [ebp + 8]
; 	float b at [ebp + 12]
; 	float * res at [ebp + 16]	

;
; code is put in the .text segment
;
segment .text
        global  mul
mul:
     
        push	ebp
        mov		ebp, esp
        push	ebx


		dump_stack 		1, 2, 4						; print out stack from ebp-8 to ebp+16
		fld 			dword [ebp+8]				; stack: a
		fld				dword [ebp+12]				; stack: b, a
		fmulp 			st1							; stack: a*b
		mov				ebx, dword [ebp+16]			;store in ebx direction of res
		fstp			dword [ebx]					; store (in res) and pop stack
        dump_regs 1               					; dump out register values
 
;
; leave
;
        

        pop		ebx
        mov		esp, ebp
        pop		ebp
                        
        ret


