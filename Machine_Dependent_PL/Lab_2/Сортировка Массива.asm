             text segment    
    assume CS:text, DS:data
begin:
    mov AX, data
    mov DS, AX
    
    mov cx, len         
    dec cx               
outer_loop:
    push cx             

    mov cx, len        
    dec cx              
    xor si, si          

inner_loop:
    mov al, mas[si]     
    mov bl, mas[si + 1] 

    cmp al, bl          
    jbe skip_swap       
    mov mas[si], bl    
    mov mas[si + 1], al 

skip_swap:
    inc si             
    loop inner_loop     

    pop cx              
    loop outer_loop     

print_array:
    mov cx, len
    mov si, 0     
    
print_loop:
    mov dl, mas[si]
    add dl, '0'
    mov ah, 02h
    int 21h
    mov dl, ' '
    int 21h
    inc si
    loop print_loop

end_p:
    mov AH, 4Ch
    mov AL, 00h
    int 21h
text ends

data segment
    mas db 1,2,3,4,10,6,7,8,9
    len equ $-mas
data ends

stk segment stack
    db 256 dup (0)
stk ends
end begin
