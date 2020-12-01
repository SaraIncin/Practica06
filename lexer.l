%{
 #include <stdio.h>
 #include "classes.h"

 int linea = 1;
%}

%%

"a" {printf("%s",yytext);fprintf(yyout, "%d", A);}
"b" {printf("%s",yytext);fprintf(yyout, "%d", B);}
"v" {fprintf(yyout, "%d", OR);}
"*" {printf("%s",yytext);fprintf(yyout, "%d", CLOSURE);}
"+" {fprintf(yyout, "%d", POSITIVE_C);}
"?" {fprintf(yyout, "%d", OPTION);}
"(" {printf("%s",yytext); fprintf(yyout, "%d", L_PAR);}
")" {printf("%s",yytext);fprintf(yyout, "%d", R_PAR);}

<<EOF>> {fprintf(yyout, "%d", EoF);yyterminate();}

. {printf("Error: %s Linea: %d\n", yytext, linea); yyterminate();}

\n {linea++; fprintf(yyout, "\n");}

%%

int check_ext(char *s, const char *ext) {
  char *e = strrchr(s, '.');
  if(!e || strcmp(e+1, ext)) {
    printf("Extension del archivo debe ser .%s\n", ext);
    return -1;
  }
  return 0;
}

int main(int argc, char *argv[]) {
  if(argc < 3) {
    puts("Se necestian dos archivos de entrada");
    return -1;
  }
  if(check_ext(argv[1], "go")==-1) return -1;
  if(check_ext(argv[2], "tokens")==-1) return -1;

  yyin = fopen(argv[1], "r");
  yyout = fopen(argv[2], "w");
  yylex();
  fclose(yyin);
  fclose(yyout);
  return 0;
}