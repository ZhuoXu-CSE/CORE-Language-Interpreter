# CORE-Language-Interpreter

CORE Language Interpreter implemented by C

Input to the interpreter
Input will come from two ASCII text files, the names of these files will be given as com- mand line arguments to the interpreter. The first file contains the program to be executed. During execution each Core input statement in the first file will read the next data value from the second file. Since Core has only integer variables, the input values in the second file will be integers, separated by spaces and/or tabs and/or newlines.

Testing the interpreter
Some test cases are provided. For each test case; (e.g. t4) there are three files (e.g. t4.code, t4.data, and t4.expected). For the tests containing valid inputs, if you compile your project with the command “gcc main.c” so it generates an executable “a.out” you need to do something like

./a.out t4.code t4.data > t4.out; diff t4.out t4.expected

You should get few differences from diff - everything should be exactly the same (slight vari- ations in the print function are allowed). 

For tests containing invalid inputs,

./a.out bad2.code bad2.data > bad2.out; cat bad2.out 

This should show an error message “ERROR: ...” in file bad2.out.


CFG of CORE Language
> <prog> ::= program <decl-seq> begin <stmt-seq> end <decl-seq> ::= <decl> | <decl><decl-seq>. 
> <stmt-seq> ::= <stmt> | <stmt><stmt-seq>. 
> <decl> ::= int <id-list> ; | <decl-func>. 
<decl-func> ::= <id> ( <id-list> ) begin <stmt-seq> endfunc ; <id-list> ::= <id> | <id> , <id-list>.
<stmt> ::= <assign> | <if> | <loop> | <in> | <out> | <func> <func> ::= begin <id> ( <id-list> ) ;.
<assign> ::= <id> = <expr> ;.
<in> ::= input <id> ;.
<out> ::= output <expr> ;.
<if> ::= if <cond> then <stmt-seq> endif ;| if <cond> then <stmt-seq> else <stmt-seq> endif ;.
<loop> ::= while <cond> begin <stmt-seq> endwhile ; <cond> ::= <cmpr> | ! ( <cond> )| <cmpr> or <cond>.
<cmpr> ::= <expr> == <expr> | <expr> < <expr> | <expr> <= <expr>.
<expr> ::= <term> | <term> + <expr> | <term> – <expr> <term> ::= <factor> | <factor> * <term>.
<factor> ::= <const> | <id> | ( <expr> ).
<const> ::= 0 | 1 | 2 | ... | 1023.
<id> ::= <letter> | <id><letter> | <id><digit>.
<letter> ::= a | b | ... | z | A | B | ... | Z.
<digit> ::= 1 | 2 | ... | 9 .
