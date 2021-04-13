push 0
pop rax
push 0
pop rbx
call :main
hlt

; translation of function implementation
main:

; translation of number
push 0

; translation of variable "n" assignment
pop [rbx+0]

; translation of "scan" function
in

; translation of variable "n" assignment
pop [rbx+0]

; translation of function call operator ("fibonacci" function)
push 1
push rbx
add
pop rcx

; translation of variable "n" access
push [rbx+0]

; translation of function call parameter
pop [rcx+0]

; move rbp before function call operator
push 1
push rbx
add
pop rbx
call :fibonacci

; retrieve function's return value
push rax

; translation of number
push 0

; translation of return operator
pop rax
ret

; translation of function implementation
fibonacci:

; translation of number
push 0

; translation of variable "f0" assignment
pop [rbx+1]

; translation of number
push 1

; translation of variable "f1" assignment
pop [rbx+2]

; translation of number
push 0

; translation of variable "prevF0" assignment
pop [rbx+3]

; translation of label for while beginning
BeginWhile0:

; translation of jump for conditional statement

; translation of variable "n" access
push [rbx+0]

; translation of number
push 1
jb :EndWhile0

; translation of variable "f1" access
push [rbx+2]

; translation of "print" function
out

; translation of variable "f0" access
push [rbx+1]

; translation of variable "prevF0" assignment
pop [rbx+3]

; translation of variable "f1" access
push [rbx+2]

; translation of variable "f0" assignment
pop [rbx+1]

; translation of variable "f1" access
push [rbx+2]

; translation of variable "prevF0" access
push [rbx+3]

; translation of '+'
add

; translation of variable "f1" assignment
pop [rbx+2]

; translation of variable "n" access
push [rbx+0]

; translation of number
push 1

; translation of '-'
sub

; translation of variable "n" assignment
pop [rbx+0]

; translation of jump to while beginning
jmp :BeginWhile0
; translation of label for while ending
EndWhile0:

; translation of number
push 0

; translation of return operator
pop rax
ret
