text       segment
           assume CS:text, DS:data

begin:     
           ; Initialize the data segment (required for DOS)
           mov AX, data          ; Load the segment address of 'data' into AX
           mov DS, AX            ; Set DS (Data Segment) to the address in AX

           ; Define a macro for logical NOT operation
           LNOT MACRO p1         ; Macro definition starts, taking one parameter p1
                xor p1, 1         ; XOR the input parameter p1 with 1 (inverts the bit)
           ENDM                  ; Macro definition ends

           ; Load the address of the TABLE into SI (Source Index)
           lea SI, TABLE         ; LEA (Load Effective Address): SI now points to the beginning of the TABLE

           ; Outer loop to iterate through values of 'a' (X1)
           loop1:               ; Loop label for the outer loop
               mov b, 0           
               loop2:             ; Loop label for the middle loop
                    mov c, 0       
                    loop3:         ; Loop label for the inner loop
                        call CALC      
                        
                        inc SI           
                        
                        inc c            ; Increment 'c' (X3)
                        cmp c, 2         ; Compare 'c' with 2 (we only need 0 and 1 for X3)
                        jl loop3         ; Jump to loop3 if c < 2, loop for X3

                    inc b              ; Increment 'b' (X2)
                    cmp b, 2           ; Compare 'b' with 2 (we only need 0 and 1 for X2)
                    jl loop2         ; Jump to loop2 if b < 2, loop for X2
               
               inc a                ; Increment 'a' (X1)
               cmp a, 2             ; Compare 'a' with 2 (we only need 0 and 1 for X1)
               jl loop1         ; Jump to loop1 if a < 2, loop for X1
               
           ; Exit the nested loops. Jump to the end of the program.
           jmp END_PROGRAM                                  
           
           ; Subroutine to calculate the function: X1?X2v(X3?X1?¬X2)
           CALC:
               ; X1 XOR X2
               mov AH, a              ; Load the value of 'a' (X1) into AH
               xor AH, b              ; XOR AH with the value of 'b' (X2), result in AH

               ; X1 AND ¬X2
               mov AL, a              ; Load the value of 'a' (X1) into AL
               mov BL, b              ; Load the value of 'b' (X2) into BL
               LNOT BL                ; Apply NOT operation to BL (¬X2) using the macro
               and AL, BL             ; AL = AL AND BL (X1 AND ¬X2)

               ; X3 OR (X1 AND ¬X2)
               or AL, c               ; AL = AL OR c (X3 OR (X1 AND ¬X2))

               ; (X1 XOR X2) NOR (X3 OR (X1 AND ¬X2))
               or AH, AL               ; AH = AH OR AL ((X1 XOR X2) OR (X3 OR (X1 AND ¬X2)))
               LNOT AH                ; Apply NOT operation to AH, the result in AH

               ; Store the result in TABLE
               mov [SI], AH             ; Store the result (AH) at the memory location pointed to by SI

               ret                     ; Return from the subroutine
                               
           END_PROGRAM:
                mov AH,4Ch             
                mov AL,00h             
                int 21h                
           
text       ends

data       segment                                 
           TABLE db 8 dup (0)       
           a     db 0                
           b     db 0                
           c     db 0              
data       ends 

stk        segment stack
           db 256 dup (0)             ; Reserve 256 bytes for the stack
stk        ends
           end begin                  ; End of the program, start execution at 'begin'