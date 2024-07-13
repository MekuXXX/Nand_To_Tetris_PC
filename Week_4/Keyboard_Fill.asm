(KEYBOARD_LOOP)

@R3
M=0

@KBD
D=M

@FINISH_KEYBOARD_LOOP
D;JEQ

@R3
M=-1

(FINISH_KEYBOARD_LOOP)
@FILL
0;JMP


(FILL)


@i 
M=0

@address
M=0

(LOOP_ROW)

@256
D=A

@i
D=D-M

@KEYBOARD_LOOP
D;JEQ


@j
M=0

(LOOP_COLOUM)
@32
D=A

@j
D=D-M

@REST_ROWS
D;JEQ



@32
D=A

@R0
M=D

@i
D=M

@R1
M=D

@MULT
0;JMP

(REST_COLUMN)
@R2
D=M

@j
D=D+M

@SCREEN
D=D+A

@address
M=D

@R3
D=M

@address
A=M
M=D

@j
M=M+1

@LOOP_COLOUM
0;JMP


(REST_ROWS)
@i
M=M+1

@LOOP_ROW
0;JMP



@R2
M=0

@index
M=0

(MULT)

@R1
D=M

@index
D=D-M

@REST_COLUMN
D;JEQ

@R0
D=M

@R2
M=D+M

@index
M=M+1

@MULT
0;JMP



