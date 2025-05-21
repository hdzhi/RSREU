text       segment
           assume CS:text,DS:data
begin:     mov AX,data           ; Load the address of the data segment into AX
           mov DS,AX             ; Set the DS register to point to the data segment
           
           lea SI, MATRIX        ; Load the effective address of MATRIX into SI (source index)
           
           mov CX, SIZE          ; Load the matrix size (4 in this case) into CX
           
           mov AX, SIZE          ; Load the size of the matrix into AX
           mov BX, 2             ; BX = 2, since each element in the matrix is a 2-byte word
           imul BX               ; Multiply BX (2) by AX (matrix size), AX = SIZE * 2
           add AX, 2             ; Add 2 to AX to account for the step size between rows (each element is 2 bytes)
           mov DX, AX            ; Store the result (step size in bytes) in DX
           
CALC_SUM:  mov AX, [SI]           ; Load the word at the current position of SI into AX
           add SUMMA, AX         ; Add the value in AX to the SUMMA variable (accumulator)
           add SI, DX            ; Move SI to the next element in the matrix (increment by step size in DX)
           loop CALC_SUM         ; Decrement CX and loop back if CX != 0 (iterates SIZE times)

           
END_PROGRAM:
           mov AH,4ch            
           mov AL,00h          
           int 21h              

text       ends

data       segment                                 
           MATRIX    DW 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 
           SIZE      DW 4             
           SUMMA     DW ?             
       
data       ends 

stk        segment stack
           db 256 dup (0)            
stk        ends

           end begin 
