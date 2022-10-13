# C-Compiler
This repository contains codes for a Compiler designed to compile C Programs for a miniature C Grammar  

## Miniature C Grammar
Program -> main() { declarations statement-list } <br/>
Declarations -> data-type identifier-list; declarations | e <br/>
data-type -> int | char <br/>
identifier-list -> id identifier-list-prime <br/>
identifier-list-prime -> , identifier-list | number number-prime | number number-prime | e <br/>
number-prime -> , identifier-list | e <br/>
statement-list -> statement statement-list | e <br/>
statement -> assign-stat; | decision-stat | looping-stat <br/>
assign-stat -> id=expn <br/>
expn -> simple-expn eprime <br/>
eprime -> relop simle-expn | e <br/>
simple-expn -> term seprime <br/>
seprime -> addop term seprime | e <br/>
term -> factor tprime <br/>
tprime -> mulop factor prime | e <br/>
factor -> id | num <br/>
decision-stat -> if (expn) {statement-list} dprime <br/>
dprime -> else {statement-list} | e <br/>
looping-stat -> while (expn) {statement-list} | for (assign-stat ; expn ; assign-stat) {statement-list} <br/>
relop -> == | != | <= | >= | > | < <br/>
add op -> + | - <br/>
mulop -> * | / | % <br/>
