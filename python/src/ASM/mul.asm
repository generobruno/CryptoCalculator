

;
; file: mul.asm

;
; Using Linux and gcc:
; nasm -f elf mul.asm
; gcc -o mul mul.o -m32 driver.c asm_io.o
;



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
;	float a at [rbp + 16]
; 	float b at [rbp + 24]
; 	float * res at [rbp + 32]	

;
; code is put in the .text segment
;
segment .text
        global  mul
mul:
     
        push	rbp
        mov	rbp, rsp
        push	rbx
        



	mulss			xmm0, xmm1
	
       
 
;
; leave
;
        

        pop		rbx		
        mov		rsp, rbp
        pop		rbp
                        
        ret


