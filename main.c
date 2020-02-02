#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

////////////////////////////////
#define MAXSIZE 100

#define NUMBER '0'
#define PRINT  '?'
#define NAME 'n'
////////////////////////////////
#define MAXBUF 100
char buf[MAXBUF];
int bufp=0;
//////////////functions/////////
int getop(char s[]);
void ungetch(int c);
int getch(void);
////////////////////////////////
#define MAXVAL 100
double val[MAXVAL];
int sp=0;
void push(double f);
double pop(void);
void clear(void);
void mathfnc(char s[]);

int main()
{
    //int y = getop(s);
    //printf("%d %s\n", y, s);
    char s[MAXSIZE];
    int i, type, var=0;
    double op2, v;
    double op1;
    double variable[26];
    for(i=0; i<26; i++){
        variable[i]=0.0;
    }

     while ((type = getop (s)) != EOF) {
        switch (type) {
        case NUMBER:
            push (atof(s));
            break;
        case PRINT:     //напечатать верхний элемент стека
            op2 =pop();           
            printf("\t%.8g\n", op2);
            push(op2);        
            break;
        case NAME:
            mathfnc(s);
            break;
        case 'c':      //очистить стек
            clear(); 
            break;
        case 'p':      //продублировать верхний элемент стека
            op2=pop();
            push(op2);
            push(op2);
            break;
        case 's':      //поменять местами верхние элементы стека
            op2=pop();
            op1=pop();
            push(op2);
            push(op1);
            break;
        case '+':
            push (pop() + pop());
            break;
        case '*':
            push (pop() * pop());
            break;
        case '-':
            op2 = pop();
            push (pop() - op2);
            break;
        case '%':
           op2 = pop();
           if(op2!=0.0){
               push(fmod(pop(), op2));
           }
           else{
               printf("Error, zero divisor!\n");
           }
           break;
        case '/':
            op2 = pop();
            if (op2 != 0.0)
                push (pop() / op2);
            else
                printf("Error, zero divisor!\n");
            break;
        case '=':
            pop();
            if(var>='A' && var<='Z'){
                variable[var-'A']=pop();
            }else
            {
                printf("Ошибка, отсутсвует имя переменной\n");
            }
            break;
        case '\n':
            v=pop();
            printf("\t%.8g\n", v);
            break;
        default:
            if(type>='A' && type <='Z'){
                push(variable[type-'A']);
            }
            else if(type=='v'){
                push(v);
            }
            else{
                printf("Error, unnoun command %s\n", s);
            }
            break;
        }
        var=type;
    }


    return 0;
}

int getop(char s[])
{
    int c,i;
    while((s[0]=c=getch())==' ' || c=='\t');
    s[1]='\0';
    i=0;
    /////////////////////////////////////////////////////////////////
    if(islower(c)){
        while(islower(s[++i]=c=getch()));
        s[i]='\0';
        if(c!=EOF){
            ungetch(c);
        }
        if(strlen(s)>1){
            return NAME;
        }else{
            return c;
        }

    }
    

    /////////////////////////////////////////////////////////////////
    if(!isdigit(c) && c!='.' && c!='-')
    {
        return c; /*не число*/
    }

    if(c=='-'){
        if(isdigit(c=getch()) || c=='.')
        {
           s[++i]=c; //отрицательное число
        }
        else{
           if(c!=EOF) ungetch(c);
           return '-';
        }
    }

    if(isdigit(c))
    {
        while (isdigit((s[++i])=c=getch()));

    }

    if(c=='.')
    {
        while (isdigit((s[++i])=c=getch()));

    }
    s[i]='\0';
    if(c!=EOF){
        ungetch(c);
    }
    

    return NUMBER;
}

    

void ungetch(int c){
    if(bufp>=MAXBUF){
        printf("Error, bufp is: %d\n", bufp);
    }else{
        buf[bufp++]=c;
    }
}

int getch(void){
    return (bufp>0)? buf[--bufp] : getchar();
}

//////////////////////////////////

void push(double f){
    if(sp<MAXVAL){
        val[sp++]=f;
    }
    else{
        printf("Error, steck is full! can't push %g\n", f);
    }
}

double pop(void){
    if(sp>0){
        return val[--sp];
    }else{
        printf("Error, steck is empty!\n");
        return 0.0;
    }
}

void clear(void)
{
    sp=0;
}

void mathfnc(char s[])
{
    double op2;
    if(strcmp(s, "sin")==0){
        push(sin(pop()));
    }
    else if(strcmp(s,"cos")==0){
        push(cos(pop()));
    }
    else if(strcmp(s, "exp")==0){
        push(exp(pop()));
    }
    else if(strcmp(s, "pow")==0){
        op2=pop();
        push(pow(pop(), op2));
    }
    else{
        printf("Error, %s doesn't supported!\n", s);
    }
}