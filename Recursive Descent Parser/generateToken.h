#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct token
{
    char* token;
    unsigned int row,col; //Line numbers.
    char* type;
};

struct token t = {NULL, 1, 1, NULL};

void printToken(struct token t)
{
    printf("<%s, %d, %d, %s>\n",t.token, t.row, t.col, t.type);
}

int isKeyword(char *s)
{
    char keywords[32][100] = {"auto", "break", "case", "char", "const", "continue", "default", "do", "double", 
                            "else", "enum", "extern", "float", "for", "goto", "if", "int", "long", "register", 
                            "return", "short", "signed", "sizeof", "static", "struct", "switch", 
                            "typedef", "union", "unsigned", "void", "volatile", "while"};

    for (int i = 0; i < 32; i++) if (strcmp(keywords[i], s) == 0) return 1;
    return 0;
}

int isSymbol(char c)
{
    char symb[15] = {'(', ')', '{', '}', ',', ';', '+', '-', '/', '*', '%', ' ', '\n', 34, 39};
    for (int i = 0; i < 15; i++) if (c == symb[i]) return 1;
    return 0;
}

void remove_whitespaces(FILE *f1, FILE *f2)
{
    char c = fgetc(f1);
    while (c != EOF)
    {
        if (c == 34)
        {
            fputc(c, f2);
            c = getc(f1);
            while (c != 34)
            {
                fputc(c, f2);
                c = fgetc(f1);
            }
            fputc(c, f2);
            c = fgetc(f1);
        }
        else if (c == 39)
        {
            fputc(c, f2);
            c = getc(f1);
            while (c != 39)
            {
                fputc(c, f2);
                c = fgetc(f1);
            }
            fputc(c, f2);
            c = fgetc(f1);
        }
        else
        {
            if (c == ' ' || c == '\t')
            {
                c = ' ';
                fputc(c, f2);
                while (c == ' ' || c == '\t') c = fgetc(f1);
            }
            else if (c == '#') while (c != '\n') c = fgetc(f1);
            else
            {
                fputc(c, f2);
                c = fgetc(f1);
            }
        }
    }
}

void remove_comments(FILE *fa, FILE *fb)
{
    char ca, cb;
    ca = fgetc(fa);

    while(ca != EOF)
    {
        if (ca == '/')
        {
            cb = getc(fa);
            if (cb == '/') while(ca != '\n') ca = getc(fa);
            else if (cb == '*')
            {
                do
                {
                    while (ca != '*') ca = getc(fa);
                    ca = getc(fa);
                }
                while (ca != '/');
            }
            else
            {
                putc(ca, fb);
                putc(cb, fb);
            }
        }
        else putc(ca, fb);
        ca = getc(fa);
    }
}

int getNextToken(char str[100], char c)
{
    int n = strlen(str);

    if (c == '\n' || str[0] == '\0') return 0;
    
    if(isKeyword(str))
    {
        t.type = "keyword";
        t.token = str;
        return 1;
    }
    else if((str[0]==34 && str[n-1]==34) || (str[0]==39 && str[n-1]==39))
    {
        t.type = "literal";
        t.token = str;
        return 1;
    }
    else if(str[0] == '=' || str[0] == '<' || str[0] == '>' || str[0] == '!')
    {
        t.type = "relational operator";
        t.token = str;
        return 1;
    }
    else if(str[0] == '+' || str[0] == '-')
    {
        t.type = "add operator";
        t.token = str;
        return 1;
    }
    else if(str[0] == '*' || str[0] == '/' || str[0] == '%')
    {
        t.type = "mul operator";
        t.token = str;
        return 1;
    }
    else if(str[0] == ')' || str[0] == '(' || str[0] == ';' || str[0] == ',' || str[0] == '}' || str[0] == '{' || str[0] == '[' || str[0] == ']')
    {
        t.type = "special symbol";
        t.token = str;
        return 1;
    }
    else if (str[0] >= '0' && str[0] <= '9')
    {
        int i = 0;
        while ((str[i] >= '0' && str[i] <= '9') && str[i] != '\0') i++;
        
        if (i == strlen(str))
        {
            t.type = "Numerical Constant";
            t.token = str;
            return 1;
        }
    }
    else if((str[0]!=c) && (c == ' ' || c == '\n' || c == ')' || c == '(' || c == ';' || c == ',' || c == '}' || c == '{'))
    {
        t.type = "identifier";
        t.token = str;
        return 1;
    }
    else return 0;
}

FILE* preprocess()
{
    FILE *f1, *f2, *f3;

    f1 = fopen("test5.c", "r");

    if (f1 == NULL)
    {
        printf("Can't Open File\n");
        exit(0);
    }

    f2 = fopen("copy.txt", "w+");
    f3 = fopen("copy2.txt", "w+");

    remove_comments(f1, f2);

    fseek(f2, 0, SEEK_SET);
    remove_whitespaces(f2, f3);

    fclose(f2);
    fclose(f3);

    f3 = fopen("copy2.txt", "r");

    return f3;
}

