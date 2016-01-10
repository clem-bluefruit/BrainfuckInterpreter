Brainfuck Interpreter
=====================
Brainfuck is an esoteric programming language noted for its extreme
minimalism. The language consists of only eight simple commands and an 
instruction pointer.
 
The language consists of eight commands, listed below.
A brainfuck program is a sequence of these commands, possibly interspersed
with other characters (which are ignored). The commands are executed 
sequentially, with some exceptions: an instruction pointer begins at the first
command, and each command it points to is executed, after which it normally 
moves forward to the next command. The program terminates when the instruction 
pointer moves past the last command.
 
Command | Meaning
--------|----------------------------------------------------------------------
>	| Increment the data pointer (to point to the next cell to the right).
<	| Decrement the data pointer (to point to the next cell to the left).
+	| Increment (increase by one) the byte at the data pointer.
-	| Decrement (decrease by one) the byte at the data pointer.
.	| Output the byte at the data pointer.
,	| Accept one byte of input, storing its value in the byte at the data
        | pointer.
[	| If the byte at the data pointer is zero, then instead of moving the
        | instruction pointer forward to the next command, jump it forward to
        | the command after the matching ] command.
]	| If the byte at the data pointer is nonzero, then instead of moving
        | the instruction pointer forward to the next command, jump it back to
        | the command after the matching [ command.
 
The brainfuck language uses a simple machine model consisting of the program
and instruction pointer, as well as an array of at least 30,000 byte cells
initialized to zero; a movable data pointer (initialized to point to the
leftmost byte of the array); and two streams of bytes for input and output 
(most often connected to a keyboard and a monitor respectively, and using the
ASCII character encoding).
1
1
BrainfuckInterpreter.cpp
BrainfuckInterpreter.hpp
BrainfuckInterpreter.tests.cpp
cyber-dojo.sh
instructions
makefile
5
35
output

help

fork from 375

close
