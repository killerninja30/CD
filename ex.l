%{
#include <stdio.h>
%}

%%
"if"|"else"|"while"|"return"|"int"|"float"|"char" { printf("Keyword: %s\n", yytext); }

[0-9]+(\.[0-9]+)? { printf("Number: %s\n", yytext); }

"+"|"-"|"*"|"/"|"=" { printf("Operator: %s\n", yytext); }

"("|")"|";"|","|"{"|"}" { printf("Delimiter: %s\n", yytext); }

[ \t\n]+ ; 

. { printf("Unknown: %s\n", yytext); }
%%

int main() {
    yylex();
    return 0;
}

