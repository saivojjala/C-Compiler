# Recursive Descent Parser
Recursive Descent Parsing is a type of Top Down parser in which a procedure is written for each and every non terminal that appears in the grammar. 

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

## Implementation 
* A C program is given as input to the parser. 
* Using the functions in generateToken.h, the parser first performs Lexical Analysis and generates tokens.
* Each time a token is generated it is passed to procedures present in the parser which check whether or not the token is accepted by the grammar.
* If all the tokens generated for a given program are present in the grammars's productions, the parser returns SUCCESS.
* If any token generated for a given program is not present in the grammar's productions, the parser returns ERROR.
* Incase of ERROR, the parser program also displays the lexeme where the error is, and the row and column of numbers corresponding to the lexeme.
* The following images shows the output of 5 test cases. Here the first 3 cases successfully compile without error as they are consistent with the given grammar. Test case 4 and 5 fail as the program's are not consistent with the given grammar.

![Parser](https://user-images.githubusercontent.com/75254081/195694432-bbd8c6ac-79a6-41f7-b102-f52d7bdffd50.png)


