text segment
   assume CS:text, DS:data
begin:
    mov AX, data
    mov DS, AX

    mov al, summand_2
    add al, summand_1

    mov sum_b, al
    jnc end_p
    adc carry, 0

end_p:
    mov AH, 4Ch
    mov AL, 00h
    int 21h
text ends

data segment
    summand_1 db 1
    summand_2 db 2
    sum_w label word
    sum_b db 0
    carry db 0
data ends

stk segment stack
    db 256 dup (0)
stk ends

end begin
