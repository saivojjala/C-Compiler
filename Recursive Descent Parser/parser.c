/*
Program -> main () { declarations assign_stat}
declarations -> data_type identifier_list; declarations | e
data_type -> int | char
identifier_list -> id identifier_list_prime;
identifier_list_prime -> , identifier_list | e
assign_stat -> id = assign_stat_prime
assign_stat_prime -> id | num
expn -> simple-expn eprime
eprime -> relop simple-expn | e
simple-exp -> term seprime
seprime -> addop term seprime | e
term -> factor tprime
tprime -> mulop factor tprime | e
factor -> id | num
relop -> == | != | <= | >= | > | <
addop -> + | -
mulop -> * | / | %


First(Program) = {int, char}
First(declarations) = {int, char, e}
First(data_type) = {int, char}
First(identifier_list) = {id}
First(list) = {, , e}
First(assign_stat) = {id}
First(identifier) = {id, num}

Follow(Program) = {$}
Follow(declarations) = {id}
Follow(data_type) = {id}
Follow(identifier_list) = {;}
Follow(list) = {;}
Follow(assign_stat) = { } }
Follow(identifier) = { } }

*/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "generateToken.h"

FILE* f;
char c;
char str[100];
const char *dtype[]={"int","char"};

void valid();
void invalid();
void program();
void declarations();
int data_type();
void identifier_list();
void identifier_list_prime();
void number_prime();
void statement_list();
void statement();
void assign_stat();
void expn();
void eprime();
void simple_exp();
void seprime();
void term();
void tprime();
void factor();
void decision_stat();
void dprime();
void looping_stat();
void relop();
void addop();
void mulop();

int main()
{
    f = preprocess();
    program();
    valid();
}

void valid()
{
    printf("-----SUCCESS-----\n");
    exit(0);
}

void invalid()
{
    printf("-----ERROR-----\n%s at row %d and column %d\n", t.token, t.row, t.col);
    exit(0);
}

void checker()
{
    int i = 0;
    int flag = 0;
    while (c != EOF)
    {
        if (c != ' ' && c != '\n' && c != ')' && c != '(' && c != ';' && c != ',' && c != '}' && c != '{' && c != 34 && c != 39)
        {
            str[i++] = c;
            flag = getNextToken(str, c);
            c = fgetc(f);
        }
        else
        {
            str[i] = '\0';
            i = 0;
            flag = getNextToken(str, c);
            if(flag==1)
            {
                t.col += strlen(str);
                return;
            }
            
            if (c == ' ')
            {
                c = fgetc(f);
                t.col++;
            }
            else if (c == 34) 
            {
                do
                {
                    str[i++] = c;
                    c = fgetc(f);    
                }
                while (c != 34);
                str[i++] = c;
                c = fgetc(f);
                if(flag==1)
                {
                    t.col += strlen(str);
                    return;
                }
            }
            else if (c == 39) 
            {
                do
                {
                    str[i++] = c;
                    c = fgetc(f);    
                }
                while (c != 39);
                str[i++] = c;
                c = fgetc(f);
                if(flag==1)
                {
                    t.col += strlen(str);
                    return;
                }
            }
            else if (c == ')' || c == '(' || c == ';' || c == ',' || c == '}' || c == '{')
            {
                str[i++] = c;
                str[i] = '\0';
                i = 0;
                flag = getNextToken(str, c);
                if(flag==1)
                {
                    c = fgetc(f);
                    t.col += strlen(str);
                    return;
                }
                c = fgetc(f);
            }
            else if (c == '\n')
            {
                c = fgetc(f);
                t.row ++;
                t.col = 1;
            }
        }
    } 
}

void program()
{
    c = fgetc(f);
    checker();
    if(strcmp(t.token,"main")==0)
    {
        checker();
        if(strcmp(t.token,"(") == 0)
        {
            checker();
            if(strcmp(t.token,")")==0)
            {
                checker();
                if(strcmp(t.token,"{")== 0)
                {
                    checker();
                    declarations();
                    statement_list();
                    if(strcmp(t.token,"}")== 0)
                    {
                        return;
                    }
                    else 
                    {
                        invalid();   
                    }
                }
                else
                {
                    invalid();
                }    
            }
            else
            {
                invalid();
            }
        }
        else
        {
            invalid();
        }
    }
    else
    {
        invalid();
    }
}

void declarations()
{
    if (data_type(t.token))
    {
        checker();
        identifier_list();   
        if (strcmp(t.token, ";") == 0)
        {
            checker();
            declarations();
        }
    }
}

int data_type(const char *str)
{
    for (int i = 0; i < sizeof(dtype) / sizeof(char *); i++)
    {
        if (strcmp(str, dtype[i]) == 0)
            return 1;
    }
    return 0;
}

void identifier_list()
{
    if (strcmp(t.type, "identifier") == 0)
    {
        checker();
        identifier_list_prime();
    }
    else
        invalid();
}

void identifier_list_prime()
{
    if (strcmp(t.token, ",") == 0)
    {
        checker();
        identifier_list();
    }
    else if(strcmp(t.token, "[")==0)
    {
        checker();
        if(strcmp(t.type, "Numerical Constant")==0)
        {
            checker();
            if(strcmp(t.token, "]")==0)
            {
                checker();
                number_prime();               
            }
        }
        else
        {
            invalid();
        }
    }
}

void number_prime()
{
    if(strcmp(t.token, ","))
    {
        checker();
        identifier_list();
    }
}

void statement_list()
{
    if(strcmp(t.type, "identifier")==0 || strcmp(t.token, "if")==0 || strcmp(t.token, "for")==0 || strcmp(t.token, "while")==0)
    {
        statement();
        statement_list();
    }

}

void statement()
{
    if(strcmp(t.type, "identifier")==0)
    {
        assign_stat();
        if((strcmp(t.token, ";")==0))
        {
            checker();
            return;
        }
        else
        {
            invalid();
        }
    }
    else if(strcmp(t.token, "if")==0)
    {
        decision_stat();
    }
    else if(strcmp(t.token, "for")==0 || (strcmp(t.token, "while")==0))
    {
        looping_stat();
    }
    else
    {
        invalid();
    }
}

void assign_stat()
{
    if (strcmp(t.type, "identifier") == 0)
    {
        checker();
        if (strcmp(t.token, "=") == 0)
        {
            checker();
            expn();
        }
        else
        {
            invalid();
        }
    }
}

void expn()
{
    simple_exp();
    eprime();
}

void eprime()
{
    if(strcmp(t.type, "relational operator") != 0)
    {
        return;
    }
    relop();
    simple_exp();
}

void simple_exp()
{
    term();
    seprime();
}

void seprime()
{
    if(strcmp(t.type, "add operator") != 0)
    {
        return;
    }
    addop();
    term();
    seprime();
}

void term()
{
    factor();
    tprime();
}

void tprime()
{
    if(strcmp(t.type, "mul operator") != 0)
    {
        return;
    }
    mulop();
    factor();
    tprime();
}

void factor()
{
    if(strcmp(t.type, "identifier")==0 || strcmp(t.type, "Numerical Constant")==0)
    {
        checker();
    }
    else
    {
        invalid();
    }
}

void decision_stat()
{
    if(strcmp(t.token, "if")==0)
    {
        checker();
        if(strcmp(t.token, "(")==0)
        {
            checker();
            expn();
            if(strcmp(t.token, ")")==0)
            {
                checker();
                if(strcmp(t.token, "{")==0)
                {
                    checker();
                    statement_list();
                    checker();
                    if(strcmp(t.token, "}")==0)
                    {
                        checker();
                        dprime();
                    }
                    else
                    {
                        invalid();
                    }
                }
                else
                {
                    invalid();
                }
            }
            else
            {
                invalid();
            }
        }
        else
        {
            invalid();
        }
    }
    else
    {
        invalid();
    }
}

void dprime()
{
    if(strcmp(t.token, "else")==0)
    {
        checker();
        if(strcmp(t.token, "{")==0)
        {
            identifier_list();
            checker();
            if(strcmp(t.token, "}")==0)
            {
                checker();
                dprime();
            }
            else
            {
                invalid();
            }
        }
        else
        {
            invalid();
        }
    }
}

void looping_stat()
{   
    if(strcmp(t.token, "while")==0)
    {
        checker();
        if(strcmp(t.token, "(")==0)
        {
            checker();
            expn();
            if(strcmp(t.token, ")")==0)
            {
                checker();
                if(strcmp(t.token, "{")==0)
                {
                    checker();
                    statement_list();
                    checker();
                    if(strcmp(t.token, "}")==0)
                    {
                        return;
                    }
                    else
                    {
                        invalid();
                    }
                }
                else
                {
                    invalid();
                }
            }
            else
            {
                invalid();
            }
        }
        else
        {
            invalid();
        }
    }
    else if(strcmp(t.token, "for")==0)
    {
        checker();
        if(strcmp(t.token, "(")==0)
        {
            checker();
            assign_stat();
            if(strcmp(t.token, ";")==0)
            {
                checker();
                expn();
                if(strcmp(t.token, ";")==0)
                {
                    checker();
                    assign_stat();
                    if(strcmp(t.token, ")")==0)
                    {
                        checker();
                        if(strcmp(t.token, "{")==0)
                        {
                            checker();
                            statement_list();
                            checker();
                            if(strcmp(t.token, "}")==0)
                            {
                                return;
                            }
                            else
                            {
                                invalid();
                            }
                        }
                        else
                        {
                            invalid();
                        }
                    }
                    else
                    {
                        invalid();
                    }
                }
                else
                {
                    invalid();
                }
            }
            else
            {
                invalid();
            }
        }
        else
        {
            invalid();
        }
    }
    else
    {
        invalid();
    }
}

void relop()
{
    if(strcmp(t.type, "relational operator")==0)
    {
        checker();
    }
    else
    {
        invalid();
    }
}

void addop()
{
    if(strcmp(t.type, "add operator")==0)
    {
        checker();
    }
    else
    {
        invalid();
    }
}

void mulop()
{
    if(strcmp(t.type, "mul operator")==0)
    {
        checker();
    }
    else
    {
        invalid();
    }
}
