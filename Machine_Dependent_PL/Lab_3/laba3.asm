text segment
    assume CS:text, DS:data
begin:  
    MOV AX, data
    MOV DS, AX

    ; Calculate z = a * c - w
    MOV AX, a
    MUL c           ; AX = a * c (result in DX:AX, but we care only about AX)
    MOV BX, AX      ; Store a * c in temporary variable BX
    SUB BX, w       ; BX = a * c - w
    MOV z, BX       ; z = a * c - w

    ; Check if z > 0
    CMP z, 0
    JG  positive_z  ; If z > 0, jump to positive_z

    ; Otherwise calculate N = (a + b) + (b + c) / w + c * w
    negative_z:
        ; (a + b)
        MOV AX, a
        ADD AX, b       ; AX = a + b
    
        ; (b + c) / w
        MOV BX, b
        ADD BX, c       ; BX = b + c
        MOV DX, 0       ; Clear DX (important before division)
        MOV AX, BX      ; AX = b + c
        DIV w           ; AX = (b + c) / w (quotient), DX = remainder (discarded)
    
        ; (a + b) + (b + c) / w
        ADD AX, a      ; AX = (a + b) + (b + c) / w
        ADD AX, b      ; AX = (a + b) + (b + c) / w
    
        ; c * w
        MOV BX, AX     ; Save intermediate result
        MOV AX, c
        MUL w          ; AX = c * w (result in AX)
    
        ADD AX, BX     ; AX = (a + b) + (b + c) / w + c * w
    
        ; N = (a + b) + (b + c) / w + c * w
        MOV N, AX
        JMP end_calculation
    
    ; If z > 0, calculate N = f + (a – b) * c / (a + b) + a
    positive_z:
        ; (a - b)
        MOV AX, a
        SUB AX, b       ; AX = a - b
    
        ; (a - b) * c
        MUL c           ; AX = (a - b) * c  (result in DX:AX, but we care only about AX)
        JO overflow      ; Check for overflow
    
        ; (a + b)
        PUSH AX         ; Save AX on the stack
        MOV AX, a
        ADD AX, b       ; AX = a + b
    
        ; (a – b) * c / (a + b)
        MOV DX, 0       ; Clear DX (important before division)
        POP BX          ; Restore value
        DIV AX           ; AX = (a - b) * c / (a + b) (quotient), DX = remainder (discarded)
        JO overflow      ; Check for overflow
    
        ; f + (a – b) * c / (a + b)
        MOV BX, AX      ; Save AX
        MOV AX, f
        ADD AX, BX      ; AX = f + (a - b) * c / (a + b)
    
        ; N = f + (a – b) * c / (a + b) + a
        ADD AX, a       ; AX = f + (a - b) * c / (a + b) + a
        MOV N, AX
        JMP end_calculation
    
    overflow:
        MOV DX, OFFSET str_overflow  ; Point to the string address in DX
        MOV AH, 09h        ; Function to display string
        INT 21h            ; Call interrupt
        MOV AX, 0          ; Assign zero value to N
        MOV N, AX
    
    end_calculation:
        MOV AH, 4Ch
        INT 21H
                 
            
data segment
        a   DW 10      
    	b   DW 5       
    	c   DW 3       
    	w   DW 2       
    	f   DW 7       

    	z   DW ?       ; Result of a * c - w
    	N   DW ?       ; Result of calculations
	str_overflow db 'Overflow Error!', 0Dh, 0Ah, '$' ; Overflow error message
data ends  

stk segment stack
        db 256 dup (0)
stk ends
    end begin