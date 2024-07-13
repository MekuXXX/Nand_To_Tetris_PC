/*
    int i = 0;

    while (i < 256)
    {
        int j = 0;

        while (j < 32) 
        {
            address = address + ( i * 32 ) + j;
            // Make this register dark
        }
        
        i = i + 1;
    }
*/

@i 
M=0

(LOOP_ROW)

@256
D=A

@i
D=D-M

@END
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
A=D+A
M=-1

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


(END)
@END
0;JMP