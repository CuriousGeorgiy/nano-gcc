push 0
pop rax
push 0
pop rbx
push 0
pop rcx
push 0
pop rdx
call :main
hlt

; translation of function implementation
factorial:

; translation of jump for conditional statement

; translation of variable "n" access
push [rbx+1]

; translation of number
push 1
ja :EndIf0

; translation of number
push 1

; translation of return operator
pop rax
ret

; translation of label for if ending
EndIf0:

; translation of variable "n" access
push [rbx+1]

; translation of function call operator ("factorial" function)
; set rcx to next rpb
push 1
push rbx
add
pop rcx

; translation of variable "n" access
push [rbx+1]

; translation of number
push 1

; translation of '-'
sub

; translation of function call parameter
pop [rcx+1]

; remember current rbp
push rbx
pop [rcx]
; move rbp before function call operator
push rcx
pop rbx
call :factorial

; retrieve function's return value
push rax
; retrieve rbp after function call operator
push [rcx]
pop rbx
; set rcx to current rbp
push rbx
pop rcx

; translation of '*'
mul

; translation of return operator
pop rax
ret

; translation of function implementation
fibonacci:

; translation of number
push 0

; translation of variable "f0" assignment
pop [rbx+2]

; translation of number
push 1

; translation of variable "f1" assignment
pop [rbx+3]

; translation of number
push 0

; translation of variable "prevF0" assignment
pop [rbx+4]

; translation of label for while beginning
BeginWhile0:

; translation of jump for conditional statement

; translation of variable "n" access
push [rbx+1]

; translation of number
push 1
jb :EndWhile0

; translation of variable "f1" access
push [rbx+3]

; translation of "print" function
out

; translation of variable "f0" access
push [rbx+2]

; translation of variable "prevF0" assignment
pop [rbx+4]

; translation of variable "f1" access
push [rbx+3]

; translation of variable "f0" assignment
pop [rbx+2]

; translation of variable "f1" access
push [rbx+3]

; translation of variable "prevF0" access
push [rbx+4]

; translation of '+'
add

; translation of variable "f1" assignment
pop [rbx+3]

; translation of variable "n" access
push [rbx+1]

; translation of number
push 1

; translation of '-'
sub

; translation of variable "n" assignment
pop [rbx+1]

; translation of jump to while beginning
jmp :BeginWhile0
; translation of label for while ending
EndWhile0:

; translation of number
push 0

; translation of return operator
pop rax
ret

; translation of function implementation
main:

; translation of number
push 0

; translation of variable "n" assignment
pop [rbx+1]

; translation of "scan" function
in

; translation of variable "n" assignment
pop [rbx+1]

; translation of function call operator ("fibonacci" function)
; set rcx to next rpb
push 6
push rbx
add
pop rcx

; translation of variable "n" access
push [rbx+1]

; translation of function call parameter
pop [rcx+1]

; remember current rbp
push rbx
pop [rcx]
; move rbp before function call operator
push rcx
pop rbx
call :fibonacci

; retrieve function's return value
push rax
; retrieve rbp after function call operator
push [rcx]
pop rbx
; set rcx to current rbp
push rbx
pop rcx

; translation of number
push 1

; translation of variable "i" assignment
pop [rbx+2]

; translation of label for while beginning
BeginWhile1:

; translation of jump for conditional statement

; translation of variable "i" access
push [rbx+2]

; translation of variable "n" access
push [rbx+1]
ja :EndWhile1

; translation of function call operator ("factorial" function)
; set rcx to next rpb
push 6
push rbx
add
pop rcx

; translation of variable "i" access
push [rbx+2]

; translation of function call parameter
pop [rcx+1]

; remember current rbp
push rbx
pop [rcx]
; move rbp before function call operator
push rcx
pop rbx
call :factorial

; retrieve function's return value
push rax
; retrieve rbp after function call operator
push [rcx]
pop rbx
; set rcx to current rbp
push rbx
pop rcx

; translation of "print" function
out

; translation of variable "i" access
push [rbx+2]

; translation of number
push 1

; translation of '+'
add

; translation of variable "i" assignment
pop [rbx+2]

; translation of jump to while beginning
jmp :BeginWhile1
; translation of label for while ending
EndWhile1:

; translation of number
push 0

; translation of variable "aCoeff" assignment
pop [rbx+3]

; translation of number
push 0

; translation of variable "bCoeff" assignment
pop [rbx+4]

; translation of number
push 0

; translation of variable "cCoeff" assignment
pop [rbx+5]

; translation of "scan" function
in

; translation of variable "aCoeff" assignment
pop [rbx+3]

; translation of "scan" function
in

; translation of variable "bCoeff" assignment
pop [rbx+4]

; translation of "scan" function
in

; translation of variable "cCoeff" assignment
pop [rbx+5]

; translation of jump for conditional statement

; translation of variable "aCoeff" access
push [rbx+3]

; translation of number
push 0
jne :EndIf1

; translation of jump for conditional statement

; translation of variable "bCoeff" access
push [rbx+4]

; translation of number
push 0
jne :EndIf2

; translation of jump for conditional statement

; translation of variable "cCoeff" access
push [rbx+5]

; translation of number
push 0
jne :EndIf3

; translation of number
push 3

; translation of "print" function
out

; translation of number
push 0

; translation of return operator
pop rax
ret

; translation of label for if ending
EndIf3:

; translation of number
push 0

; translation of "print" function
out

; translation of number
push 0

; translation of return operator
pop rax
ret

; translation of label for if ending
EndIf2:

; translation of number
push 1

; translation of "print" function
out

; translation of number
push 0

; translation of variable "cCoeff" access
push [rbx+5]

; translation of '-'
sub

; translation of variable "bCoeff" access
push [rbx+4]

; translation of '/'
div

; translation of "print" function
out

; translation of number
push 0

; translation of return operator
pop rax
ret

; translation of label for if ending
EndIf1:

; translation of function call operator ("discriminant" function)
; set rcx to next rpb
push 6
push rbx
add
pop rcx

; translation of variable "aCoeff" access
push [rbx+3]

; translation of function call parameter
pop [rcx+1]

; translation of variable "bCoeff" access
push [rbx+4]

; translation of function call parameter
pop [rcx+2]

; translation of variable "cCoeff" access
push [rbx+5]

; translation of function call parameter
pop [rcx+3]

; remember current rbp
push rbx
pop [rcx]
; move rbp before function call operator
push rcx
pop rbx
call :discriminant

; retrieve function's return value
push rax
; retrieve rbp after function call operator
push [rcx]
pop rbx
; set rcx to current rbp
push rbx
pop rcx

; translation of variable "discriminant" assignment
pop [rbx+6]

; translation of jump for conditional statement

; translation of variable "discriminant" access
push [rbx+6]

; translation of number
push 0
jae :EndIf4

; translation of number
push 0

; translation of "print" function
out

; translation of number
push 0

; translation of return operator
pop rax
ret

; translation of label for if ending
EndIf4:

; translation of jump for conditional statement

; translation of variable "discriminant" access
push [rbx+6]

; translation of number
push 0
jne :EndIf5

; translation of number
push 1

; translation of "print" function
out

; translation of variable "discriminant" access
push [rbx+6]

; translation of "sqrt" function
sqrt

; translation of variable "bCoeff" access
push [rbx+4]

; translation of '-'
sub

; translation of number
push 2

; translation of variable "aCoeff" access
push [rbx+3]

; translation of '*'
mul

; translation of '/'
div

; translation of "print" function
out

; translation of number
push 0

; translation of return operator
pop rax
ret

; translation of label for if ending
EndIf5:

; translation of number
push 2

; translation of "print" function
out

; translation of variable "discriminant" access
push [rbx+6]

; translation of "sqrt" function
sqrt

; translation of variable "bCoeff" access
push [rbx+4]

; translation of '-'
sub

; translation of number
push 2

; translation of variable "aCoeff" access
push [rbx+3]

; translation of '*'
mul

; translation of '/'
div

; translation of "print" function
out

; translation of number
push 0

; translation of variable "discriminant" access
push [rbx+6]

; translation of "sqrt" function
sqrt

; translation of '-'
sub

; translation of variable "bCoeff" access
push [rbx+4]

; translation of '-'
sub

; translation of number
push 2

; translation of variable "aCoeff" access
push [rbx+3]

; translation of '*'
mul

; translation of '/'
div

; translation of "print" function
out

; translation of number
push 0

; translation of return operator
pop rax
ret

; translation of function implementation
discriminant:

; translation of variable "bCoeff" access
push [rbx+2]

; translation of number
push 2

; translation of '^'
pow

; translation of number
push 4

; translation of variable "aCoeff" access
push [rbx+3]

; translation of variable "cCoeff" access
push [rbx+1]

; translation of '*'
mul

; translation of '*'
mul

; translation of '-'
sub

; translation of return operator
pop rax
ret
