

;
; file: mul.asm
; First assembly program. This program asks for two integers as
; input and prints out their sum.
;
; To create executable:
; Using djgpp:
; nasm -f coff first.asm
; gcc -o first first.o driver.c asm_io.o
;
; Using Linux and gcc:
; nasm -f elf first.asm
; gcc -o first first.o driver.c asm_io.o
;
; Using Borland C/C++
; nasm -f obj first.asm
; bcc32 first.obj driver.c asm_io.obj
;
; Using MS C/C++
; nasm -f win32 first.asm
; cl first.obj driver.c asm_io.obj
;
; Using Open Watcom
; nasm -f obj first.asm
; wcl386 first.obj driver.c asm_io.obj

%include "asm_io.inc"
;
; initialized data is put in the .data segment
;
segment .data
;
; These labels refer to strings used for output
;

outmsg1 db    "You entered ", 0
outmsg2 db    " and ", 0
outmsg3 db    ", the product of these is ", 0


;
; uninitialized data is put in the .bss segment
;
segment .bss
;
; These labels refer to double words used to store the inputs
;
;	Parameters:
;	int a at [ebp + 8]
; int b at [ebp +12]

;
; code is put in the .text segment
;
segment .text
        global  mul
mul:
        enter   0,0               ; setup routine
        pusha


				dump_stack 1, 2, 4				; print out stack from ebp-8 to ebp+16
        mov     eax, [ebp+8]      ; eax = a
        mov			ebx, [ebp+12]			; ebx = b
        imul    ebx, eax     			; ebx = ebx * eax (a * b)
        dump_regs 1               ; dump out register values
        dump_mem 2, outmsg1, 1    ; dump out memory
;
; next print out result message as series of steps
;
        mov     eax, outmsg1
        call    print_string      ; print out first message
        mov     eax, [ebp+8]     	; 
        call    print_int         ; print out input1
        mov     eax, outmsg2
        call    print_string      ; print out second message
        mov     eax, [ebp+12]
        call    print_int         ; print out input2
        mov     eax, outmsg3
        call    print_string      ; print out third message
        mov     eax, ebx
        call    print_int         ; print out sum (ebx)
        call    print_nl          ; print new-line

        popa
        leave                     
        ret


