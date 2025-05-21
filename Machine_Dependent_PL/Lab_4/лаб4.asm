text segment
        assume CS:text, DS:data
begin:

        mov AX, data              ; Load the data segment into AX
        mov DS, AX                ; Set the data segment register

        mov CX, arrayLength       ; CX = Loop counter (number of elements)
        lea SI, byteArray         ; SI = Source Index (points to current array element)

process_array_loop:
        mov AL, [SI]              ; AL = Current byte from array
        test AL, 1                ; Check if even (LSB = 0)
        jz  is_even_element       ; Jump to is_even_element if even

        jmp not_even_element      ; Jump past even processing

is_even_element:
        mov AH, 0                 ; Extend AL into AX
        add sumEven, AX           ; Add even element to sum
        inc evenCount             ; Increment counter for even elements

not_even_element:
        inc SI                    ; Increment SI to point to next element
        loop process_array_loop   ; Decrement CX and loop if not zero

        cmp evenCount, 0          ; Compare evenCount with zero
        jne end_processing        ; Jump to end if even elements were found


        mov CX, arrayLength        ; Reset loop counter
        mov SI, OFFSET byteArray    ; Reset SI to start of array
        mov BX, 0                   ; BX = Flag (0 or 1) for every second element

increment_every_second_loop:
        cmp BX, 1                  ; Compare BX with 1
        je increment_this_element  ; Jump if it's the second element

        inc BX                      ; Set flag BX = 1
        jmp next_element           ; Jump past incrementing

increment_this_element:
        inc [SI]         ; Increment the byte at [SI]
        mov BX, 0                   ; Reset flag BX = 0

next_element:
        inc SI                      ; Increment SI to point to next element
        loop increment_every_second_loop  ; Decrement CX and loop

end_processing:
        mov AH, 4CH               ; Function code for program termination
        int 21H                  ; Call DOS interrupt to terminate

text ends

data segment
        byteArray DB 1, 2, 3, 2, 5, 1, 7, 1, 9, 1   ; Example byte array
        arrayLength = $ - byteArray                             ; Length of the array
        sumEven DW 0                               ; Initialize sum of even elements
        evenCount DW 0                              ; Initialize counter
data ends

stk segment stack
        db 256 dup (0)           ; Allocate stack space of 256 bytes
stk ends

end begin