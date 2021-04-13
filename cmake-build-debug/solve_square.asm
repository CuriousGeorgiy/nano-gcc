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

; translation of variable "aCoeff" assignment
pop [rbx+0]

; translation of number
push 0

; translation of variable "bCoeff" assignment
pop [rbx+1]

; translation of number
push 0

; translation of variable "cCoeff" assignment
pop [rbx+2]

; translation of "scan" function
in

; translation of variable "aCoeff" assignment
pop [rbx+0]

; translation of "scan" function
in

; translation of variable "bCoeff" assignment
pop [rbx+1]

; translation of "scan" function
in

; translation of variable "cCoeff" assignment
pop [rbx+2]

; translation of jump for conditional statement

; translation of variable "aCoeff" access
push [rbx+0]

; translation of number
push 0
jne :EndIf0

; translation of jump for conditional statement

; translation of variable "bCoeff" access
push [rbx+1]

; translation of number
push 0
jne :EndIf1

; translation of jump for conditional statement

; translation of variable "cCoeff" access
push [rbx+2]

; translation of number
push 0
jne :EndIf2

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
EndIf2:

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
EndIf1:

; translation of number
push 1

; translation of "print" function
out

; translation of number
push 0

; translation of variable "cCoeff" access
push [rbx+2]

; translation of '-'
sub

; translation of variable "bCoeff" access
push [rbx+1]

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
EndIf0:

; translation of function call operator ("discriminant" function)
push 4
push rbx
add
pop rcx

; translation of variable "aCoeff" access
push [rbx+0]

; translation of function call parameter
pop [rcx+0]

; translation of variable "bCoeff" access
push [rbx+1]

; translation of function call parameter
pop [rcx+1]

; translation of variable "cCoeff" access
push [rbx+2]

; translation of function call parameter
pop [rcx+2]

; move rbp before function call operator
push 4
push rbx
add
pop rbx
call :discriminant

; retrieve function's return value
push rax

; translation of variable "discriminant" assignment
pop [rbx+3]

; translation of jump for conditional statement

; translation of variable "discriminant" access
push [rbx+3]

; translation of number
push 0
jae :EndIf3

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
EndIf3:

; translation of jump for conditional statement

; translation of variable "discriminant" access
push [rbx+3]

; translation of number
push 0
jne :EndIf4

; translation of number
push 1

; translation of "print" function
out

; translation of variable "discriminant" access
push [rbx+3]

; translation of "sqrt" function
sqrt

; translation of variable "bCoeff" access
push [rbx+1]

; translation of '-'
sub

; translation of number
push 2

; translation of variable "aCoeff" access
push [rbx+0]

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
EndIf4:

; translation of number
push 2

; translation of "print" function
out

; translation of variable "discriminant" access
push [rbx+3]

; translation of "sqrt" function
sqrt

; translation of variable "bCoeff" access
push [rbx+1]

; translation of '-'
sub

; translation of number
push 2

; translation of variable "aCoeff" access
push [rbx+0]

; translation of '*'
mul

; translation of '/'
div

; translation of "print" function
out

; translation of number
push 0

; translation of variable "discriminant" access
push [rbx+3]

; translation of "sqrt" function
sqrt

; translation of '-'
sub

; translation of variable "bCoeff" access
push [rbx+1]

; translation of '-'
sub

; translation of number
push 2

; translation of variable "aCoeff" access
push [rbx+0]

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
push [rbx+1]

; translation of number
push 2

; translation of '^'
pow

; translation of number
push 4

; translation of variable "aCoeff" access
push [rbx+2]

; translation of variable "cCoeff" access
push [rbx+0]

; translation of '*'
mul

; translation of '*'
mul

; translation of '-'
sub

; translation of return operator
pop rax
ret
