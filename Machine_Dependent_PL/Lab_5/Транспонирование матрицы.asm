text       segment
           assume CS:text, DS:data
begin:     mov AX, data
           mov DS, AX
           
           mov AX, 0
           
           OUTER_LOOP:
                mov BX, 0
                INNER_LOOP:
                    call SWAP
                    
                    inc BX
                    
                    cmp BX, SIZEX
                    
                    jl INNER_LOOP
                    
                inc AX
                cmp AX, SIZEY
                
                jl OUTER_LOOP
                    
           jmp END_PROGRAM
                     
           SWAP: 
                push AX 
                push BX 
                
                mov DX, SIZEX
                call CALC_OFFSET
                
                mov SI, CX
                
                xchg AX, BX
                
                mov DX, SIZEY
                call CALC_OFFSET 
                
                mov DI, CX
                
                mov DX, MATRIX[SI]
                
                mov MATRIX2[DI], DX 
                
                pop BX
                pop AX
                
                ret
                
           CALC_OFFSET:
                mov CX, AX
                mul DX
                add AX, BX
                mov DX, 2
                mul DX
                         
                xchg CX, AX
                
                ret
           
           END_PROGRAM:
                mov AH,4Ch
                mov AL,00h
                int 21h  
           
text       ends

data       segment                                 
           MATRIX    DW 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16
           
           SIZEX     DW 3
           SIZEY     DW 4
           MATRIX2   DW SIZEX * SIZEY dup (?)
       
data       ends 

stk        segment stack
           db 256 dup (0)
stk        ends
           end begin
