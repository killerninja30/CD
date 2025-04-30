%{
#include <stdio.h>
%}

%%
--[^\n]*                      ; // Ignore single-line comments (--)  
"SELECT"|"FROM"|"WHERE"|"INSERT"|"INTO"|"VALUES"|"UPDATE"|"SET"|"DELETE"|"CREATE"|"TABLE"|"DROP"|"AND"|"OR"|"ALL" {
    printf("Keyword: %s\n", yytext);
}

[0-9]+(\.[0-9]+)?             { printf("Number: %s\n", yytext); }

'([^']*)'                     { printf("String Literal: %s\n", yytext); }

"="|"<"|">"|"<="|">="|"<>"    { printf("Operator: %s\n", yytext); }

"("|")"|","|";"               { printf("Delimiter: %s\n", yytext); }

[a-zA-Z_][a-zA-Z0-9_]*        { printf("Identifier: %s\n", yytext); }

[ \t\n\r]+                    ; // Ignore whitespace

.                             { printf("Unknown: %s\n", yytext); }
%%

int main() {
    yylex(); // Start lexical analysis
    return 0;
}

int yywrap() {
    return 1;
}
