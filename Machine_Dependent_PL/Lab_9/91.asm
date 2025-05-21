init MACRO
    mov AX, data
    mov DS, AX
ENDM          

end_program MACRO
    mov AH, 4Ch
    mov AL, 00h
    int 21h  
ENDM
    
text       segment
           assume CS:text, DS:data
begin:     init
;6.	N = (a + c) * (b + c) / w + c + w;
           fild a          ; Загружаем a в st(0)
           fild b          ; Загружаем b в st(0), a перемещается в st(1)
           fsub            ; st(0) = a - b
           fild d          ; Загружаем d в st(0), результат (a-b) в st(1)
           fsub            ; st(0) = (a - b) - d
           fild w          ; Загружаем w в st(0), результат (a-b-d) в st(1)
           fmul            ; st(0) = (a - b - d) * w
           fild a          ; Загружаем a в st(0), предыдущий результат в st(1)
           fild w          ; Загружаем w в st(0), a в st(1), предыдущий результат в st(2)
           fsub            ; st(0) = a - w
           fdiv            ; st(0) = (a - b - d) * w / (a - w)
           fild cp         ; Загружаем c в st(0), предыдущий результат в st(1)
           fadd            ; st(0) = c + (a - b - d) * w / (a - w)
           fistp z         ; Сохраняем результат в z и извлекаем из стека
           end_program
text       ends

data       segment                                 
           a dw 5
           b dw 2
           d dw 1
           cp dw 3
           w dw 2
           z dw ?      
data       ends 

stk        segment stack
           db 256 dup (0)
stk        ends
           end begin