push 0
pop rax
push 0
pop rbx
call :main
hlt

; translation of function implementation
factorial:

; translation of jump for conditional statement

; translation of variable "n" access
push [rbx+0]

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
push [rbx+0]

; translation of function call operator ("factorial" function)
push 1
push rbx
add
pop rcx

; translation of variable "n" access
push [rbx+0]

; translation of number
push 1

; translation of '-'
sub

; translation of function call parameter
pop [rcx+0]

; move rbp before function call operator
push 1
push rbx
add
pop rbx
call :factorial

; retrieve function's return value
push rax

; translation of '*'
mul

; translation of return operator
pop rax
ret

; translation of function implementation
main:

; translation of "scan" function
in

; translation of variable "n" assignment
pop [rbx+0]

; translation of function call operator ("factorial" function)
push 1
push rbx
add
pop rcx

; translation of number
push 2

; translation of variable "n" access
push [rbx+0]

; translation of '*'
mul

; translation of number
push 1

; translation of '+'
add

; translation of function call parameter
pop [rcx+0]

; move rbp before function call operator
push 1
push rbx
add
pop rbx
call :factorial

; retrieve function's return value
push rax

; translation of number
push 7

; translation of '+'
add

; translation of "print" function
out
