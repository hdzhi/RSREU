; stack initialization
stacksg segment para stack 'stack'
        dw  32 DUP(?)
stacksg ends

; data segment with strings whth somwthing written and empty one
datasg segment para 'Data'
           
CONAME DB 'meow meow meow.'  
PRLINE DB 20 DUP(' ')       
           
datasg ends



codesg segment para 'Code'

main:   
;show what segm we will use
	assume CS:CODESG,DS:DATASG,SS:STACKSG,ES:DATASG   
	; stask segm. initail....
	PUSH DS
	SUB AX,AX
	PUSH AX     
	
	MOV AX, DATASG 
	MOV DS,AX
	MOV ES,AX
	          ;copy operation
	 cld
	 mov cx, 20
	 lea DI, PRLINE
	 lea SI, CONAME
	 REP MOVSB
	
	
	mov	ax,4c00h
	int	21h
end	main     

codes ends