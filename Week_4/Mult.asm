@R2
M=0

@index
M=0



(MULT)


@R1
D=M

@index
D=D-M

@END
D;JEQ

@R0
D=M

@R2
M=D+M

@index
M=M+1

@MULT
0;JMP



(END)
@END
0;JMP
