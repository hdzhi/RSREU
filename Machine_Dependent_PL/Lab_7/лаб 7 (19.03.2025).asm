.MODEL SMALL
.STACK 100H

DATA SEGMENT
    message DB "Hello, world!$"
    num1 DW 10
    num2 DW 20
    result DW ?
    stack_message DB "Message from stack: ", 0 ; No $ here!
    stack_message_len EQU $-stack_message
DATA ENDS

TEXT SEGMENT
    ASSUME CS:TEXT, DS:DATA

; Macros
INIT_DATA MACRO
    MOV AX, DATA
    MOV DS, AX
ENDM

PRINT_STRING MACRO string_address
    LEA DX, string_address
    MOV AH, 09H
    INT 21H
ENDM

EXIT_PROGRAM MACRO
    MOV AH, 4CH
    MOV AL, 00H
    INT 21H
ENDM

; Procedure taking arguments via registers
ADD_REGISTERS PROC NEAR
    ADD AX, BX
    RET
ADD_REGISTERS ENDP

; Procedure taking arguments via the stack
PRINT_STACK_MESSAGE PROC NEAR
    PUSH BP
    MOV BP, SP

    MOV DX, OFFSET stack_message ;Print prefix
    MOV AH, 09H
    INT 21H

    MOV DX, [BP+4] ;Get pointer to stack stored message
    MOV AH, 09H
    INT 21H

    POP BP
    RET 2
PRINT_STACK_MESSAGE ENDP

MAIN PROC
    MOV AX, DATA
    MOV DS, AX ;Initialize data segment
    INIT_DATA ; Initialize data segment  (повторный вызов удален)

    ; Example usage of ADD_REGISTERS
    MOV AX, num1
    MOV BX, num2
    CALL ADD_REGISTERS
    MOV result, AX

    ; Example usage of PRINT_STACK_MESSAGE
    PUSH OFFSET message ; push the offset of the string to the stack
    CALL PRINT_STACK_MESSAGE
    ADD SP, 2

    ; Display the string from memory
    PRINT_STRING message

    ; Program termination
    EXIT_PROGRAM
MAIN ENDP

TEXT ENDS
END MAIN