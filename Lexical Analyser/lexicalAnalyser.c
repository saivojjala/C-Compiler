#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct token
{
    char* token;
    unsigned int row,col; //Line numbers.
    char* type;
};

struct token t;

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
    // printf("%s\n", str);
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
    else if(str[0] == '=' || str[0] == '+' || str[0] == '<' || str[0] == '>')
    {
        t.type = "operator";
        t.token = str;
        return 1;
    }
    else if(str[0] == ')' || str[0] == '(' || str[0] == ';' || str[0] == ',' || str[0] == '}' || str[0] == '{')
    {
        t.type = "special symbol";
        t.token = str;
        return 1;
    }
    else if((str[0]!=c) && (c == ' ' || c == '\n' || c == ')' || c == '(' || c == ';' || c == ',' || c == '}' || c == '{'))
    {
        t.type = "identifier";
        t.token = str;
        return 1;
    }
    else return 0;
}

void checker(FILE *f3)
{
    char str[100];
    t.row = 1;
    t.col = 1;
    int i = 0;
    char c = fgetc(f3);
    int flag = 0;
    while (c != EOF)
    {
        if (c != ' ' && c != '\n' && c != ')' && c != '(' && c != ';' && c != ',' && c != '}' && c != '{' && c != 34 && c != 39)
        {
            str[i++] = c;
            flag = getNextToken(str, c);
            c = fgetc(f3);
        }
        else
        {
            str[i] = '\0';
            i = 0;
            flag = getNextToken(str, c);
            if(flag==1)
            {
                printToken(t);
                t.col += strlen(str);
            }
            
            if (c == ' ')
            {
                c = fgetc(f3);
                t.col++;
            }
            else if (c == 34) 
            {
                do
                {
                    str[i++] = c;
                    c = fgetc(f3);    
                }
                while (c != 34);
                str[i++] = c;
                c = fgetc(f3);
                if(flag==1)
                {
                    printToken(t);
                    t.col += strlen(str);
                }
            }
            else if (c == 39) 
            {
                do
                {
                    str[i++] = c;
                    c = fgetc(f3);    
                }
                while (c != 39);
                str[i++] = c;
                c = fgetc(f3);
                if(flag==1)
                {
                    printToken(t);
                    t.col += strlen(str);
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
                    printToken(t);
                    t.col += strlen(str);
                }
                c = fgetc(f3);
            }
            else if (c == '\n')
            {
                c = fgetc(f3);
                t.row ++;
                t.col = 1;
            }
        }
    }
}

FILE* preprocess()
{
    FILE *f1, *f2, *f3;

    f1 = fopen("sample.c", "r");

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

int main()
{
    FILE* f;
    f = preprocess();
    checker(f);
}