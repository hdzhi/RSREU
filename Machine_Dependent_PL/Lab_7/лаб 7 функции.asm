INIT MACRO
    MOV AX, DATA
    MOV DS, AX
ENDM          

END_PROGRAM MACRO
    MOV AH, 4Ch
    MOV AL, 00h
    INT 21h  
ENDM

PRINT MACRO str
    MOV DX, OFFSET str
    MOV AH, 09h
    INT 21h       
ENDM

TEXT SEGMENT
    ASSUME CS:TEXT, DS:DATA
BEGIN:     
    INIT

    PRINT msg
    
    MOV AX, a
    MOV BX, b
    
    CALL sub_reg

    MOV c, AX 
    
    Push a
    push b
    
    call sub_stack
    mov d, AX

    END_PROGRAM
    
    sub_stack PROC  
        PUSH BP
        MOV BP, SP

        MOV AX, [BP+6]  
        SUB AX, [BP+4]  

        POP BP
        RET 4           
    sub_stack ENDP       
                   
    sub_reg PROC 
      
        SUB AX, BX
        RET         
    sub_reg ENDP
TEXT ENDS

DATA SEGMENT                                 
    msg    DB      "Meow Meow Meow Meow Meow Meow$"
    a      DW 10
    b      DW 37
    c      DW ?
    d      DW ?    
DATA ENDS 

STK SEGMENT STACK
    DB 256 DUP (0)
STK ENDS
END BEGIN