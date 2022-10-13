# Recursive Descent Parser
Recursive Descent Parsing is a type of Top Down parser in which a procedure is written for each and every non terminal that appears in the grammar. 

## Implementation 

### Miniature C Grammar
Program -> main() { declarations statement-list }
Declarations -> data-type identifier-list; declarations | e
data-type -> int | char
identifier-list -> id identifier-list-prime
identifier-list-prime -> , identifier-list | number number-prime | number number-prime | e
number-prime -> , identifier-list | e
statement-list -> statement statement-list | e
statement -> assign-stat; | decision-stat | looping-stat
assign-stat -> id=expn
expn -> simple-expn eprime
eprime -> relop simle-expn | e
simple-expn -> term seprime 
seprime -> addop term seprime | e
term -> factor tprime
tprime -> mulop factor prime | e
factor -> id | num 
decision-stat -> if (expn) {statement-list} dprime 
dprime -> else {statement-list} | e
looping-stat -> while (expn) {statement-list} | for (assign-stat ; expn ; assign-stat) {statement-list}
relop -> == | != | <= | >= | > | <
add op -> + | -
mulop -> * | / | %
