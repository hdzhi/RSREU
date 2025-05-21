init MACRO
    mov AX, data
    mov DS, AX
ENDM          

end_program MACRO
    mov AH, 4Ch
    mov AL, 00h
    int 21h  
ENDM

input MACRO dest
    LOCAL enter_text, loop_end, create_number
    
    mov si, 0
    mov cx, max_len
    
    enter_text:
        mov ah, 1h
        int 21h
        
        cmp al, 13
        je loop_end
        
        sub al, 30h
        
        mov buffer[si], al
        inc si
        
        loop enter_text
        
    loop_end:
        mov count, si
    
    mov si, 0
    mov cx, count
    xor ax, ax
    mov temp, 0
    
    create_number:
        mov ax, temp
        mov dx, 10
        imul dx
        mov temp, ax
                
        mov bl, buffer[si]
        add temp, bx
        
        inc si
        
        loop create_number
        
    mov ax, temp
    mov dest, ax      
ENDM

convert MACRO src, dest
    LOCAL convert_loop
    
    mov si, max_bin_len
    dec si
            
    convert_loop:
        xor dx, dx
        mov bx, 2
        idiv bx
                
        mov dest[si], dl
                
        dec si
                
        cmp ax, 0
        jg convert_loop
ENDM
    
text       segment
           assume CS:text, DS:data
begin:     init

           input result 
           convert result, binary
           
           end_program
                   
           
text       ends
data       segment 
max_len     =  4
buffer      db max_len dup (0)
count       dw 0
temp        dw 0
result      dw 0 
max_bin_len = 16
binary      db max_bin_len dup (0)    
data       ends 

stk        segment stack
           db 256 dup (0)
stk        ends
           end begin
