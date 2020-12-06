#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "stack.c"

#define TERM 1
#define NON_TERM 2
#define EPSILON 3
#define NUM_TERM 9
#define NUM_NON_TERM 7

sym NUT[] = {
    {TERM, "(", 0}, //0
    {TERM, ")", 1}, //1
    {TERM, "a", 2}, //2
    {TERM, "b", 3}, //3
    {TERM, "$", 4}, //4
    {TERM, "v", 5}, //5
    {TERM, "*", 6}, //6
    {TERM, "+", 7}, //7
    {TERM, "?", 8}, //8
    {NON_TERM, "S",  0}, //9
    {NON_TERM, "S'", 1}, //10
    {NON_TERM, "E", 2}, //11
    {NON_TERM, "E'", 3}, //12
    {NON_TERM, "F",  4}, //13
    {NON_TERM, "F'", 5}, //14
    {NON_TERM, "G",  6}, //15
};

prod PRODUCTIONS[] = {
    {9, "11/10", 2}, // 0 S -> ES'
    {10, "5/11/10", 3}, // 1 S' -> vES'
    {10, "-1", 0}, // 2 S' -> epsilon
    {11, "13/12", 2}, // 3 E -> FE'
    {12, "13/12", 2}, // 4 E' -> FE'
    {12, "-1", 0}, // 5 E'-> epsilon
    {13, "15/14", 2}, // 6 F -> GF'
    {14, "6/14", 2}, // 7 F' -> *F' 
    {14, "7/14", 2}, // 8 F' -> +F'
    {14, "8/14", 2}, // 9 F' -> ?F'
    {14, "-1", 0}, // 10 F' -> epsilon
    {15, "0/9/1", 3}, // 11 G -> (S)
    {15, "2", 1}, // 12 G -> a
    {15, "3", 1}, // 13 G -> b
};

int ANALYSIS_TABLE[NUM_NON_TERM][NUM_TERM] = {
    {0, -1, 0, 0, -1, -1, -1, -1, -1},
    {-1, 2, -1, -1, 2, 1, -1, -1, -1},
    {3, -1, 3, 3, -1, -1, -1, -1, -1},
    {4, 5, 4, 4, 5, 5, -1, -1, -1},
    {6, -1, 6, 6, -1, -1, -1,-1,-1},
    {10, 10, 10, 10, 10, 10, 7, 8, 9},
    {11, -1, 12, 13, -1, -1, -1, -1, -1},
};

int split (char *str, char c, char ***arr)
{
    int count = 1;
    int token_len = 1;
    int i = 0;
    char *p;
    char *t;

    p = str;
    while (*p != '\0')
    {
        if (*p == c)
            count++;
        p++;
    }

    *arr = (char**) malloc(sizeof(char*) * count);
    if (*arr == NULL)
        exit(1);

    p = str;
    while (*p != '\0')
    {
        if (*p == c)
        {
            (*arr)[i] = (char*) malloc( sizeof(char) * token_len );
            if ((*arr)[i] == NULL)
                exit(1);

            token_len = 0;
            i++;
        }
        p++;
        token_len++;
    }
    (*arr)[i] = (char*) malloc( sizeof(char) * token_len );
    if ((*arr)[i] == NULL)
        exit(1);

    i = 0;
    p = str;
    t = ((*arr)[i]);
    while (*p != '\0')
    {
        if (*p != c && *p != '\0')
        {
            *t = *p;
            t++;
        }
        else
        {
            *t = '\0';
            i++;
            t = ((*arr)[i]);
        }
        p++;
    }

    return count;
}

/*
 * Para ver más detalladamente el proceso puede descomentar
 * los printf comentados.
 * returns: un valor booleano; 0 si la cadena es rechazada y 
 *          1 si es aceptada.
 */
bool parse(char* w)
{
  stack *stack = newStack();
  push(stack, &NUT[4]);
  push(stack, &NUT[9]);
  int i= 0;
  int m=0;
  sym ip = NUT[(int)w[m]-'0'];  
  sym elem = top(stack);
  
  while(strcmp(elem.name, "$") != 0)
  {
    if(compareSym(elem,ip))
    {
        pop(stack);
        m++;
        ip = NUT[(int)w[m]-'0'];
        //printf("Avanzar con %s\n",ip.name);
    }
    else if (elem.type == TERM)
    {
        return false;
    }
    else if (ANALYSIS_TABLE[elem.pos][ip.pos] != -1)
    {
        int p =  ANALYSIS_TABLE[elem.pos][ip.pos];
        prod production = PRODUCTIONS[p];
        //printf("Produccion: %s\n", production.body);
        pop(stack);

        int c = 0;
        char **arr = NULL;

        c = split(production.body, '/', &arr);
        for (i = c-1; i >= 0; i--)
	{
            int pos = atoi(arr[i]);
            //printf("el simbolo es:%d\n ", pos);
	    
            if(pos != -1)
	    {
                 push(stack, &NUT[pos]);
            }
        }
    }
    else if (ANALYSIS_TABLE[elem.pos][ip.pos] == -1)
    {
      //printf("elem%s\n",elem.name);
      //printf("ip%s\n",ip.name);
      //printf("no prod");
        return false;
    }
    
    elem = top(stack);
    //printf("Tope pila: %s\n",elem.name);
  }
  
  return true;
}

int check_ext(char *s, const char *ext)
{
  char *e = strrchr(s, '.');
  
  if(!e || strcmp(e+1, ext))
  {
    printf("Extension del archivo debe ser .%s\n", ext);
    return -1;
  }
  
  return 0;
}

int main(int argc, char *argv[])
{
    FILE *fp;
    char linea[1024];
    
    if(argc < 2)
    {
        puts("Se necestian un archivo de entrada");
        return -1;
    }
    
    if(check_ext(argv[1], "tokens")==-1) return -1;

    fp = fopen(argv[1], "r");

    while(fgets(linea, 1024, (FILE*) fp))
    {
      //printf("%s\n",linea);
        printf("%d\n",parse(linea));
    }
    
    fclose(fp);
    
    return 0;
}
