# Práctica 06

##### Instrucciones de compilacion.

Para compilar el lexer:
- flex lexer.l
- gcc lex.yy.c -o <archivo-salida-lexer> -lfl
- ./<archivo-salida-lexer> <archivo-prueba>.go <archivo-tokens>.tokens
  
Para ejecutar el parser:
- gcc -o <salida> parser.c
- ./<salida> <archivo.tokens>.tokens
  
En el archivo **prueba.go** hay un ejemplo para pasar al lexer.

#### Nombres:
- Escamilla Monroy Miguel Ángel
- Montes Incin Sara Doris
- Orozco Viveros Carlos Eduardo
