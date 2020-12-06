#include <stdio.h>
#include <stdbool.h>
typedef struct _symbol
{
    short type; 
    char name[15];
    short pos;
} sym;

typedef struct _production
{               //S -> EF
    short head; //S 0
    char *body; //EF "2/3"
    short num;  //2

} prod;


typedef struct  _node node;
typedef struct  _stack stack;

struct _node
{
    sym info;
    node *previous;
};

struct _stack
{
    node *first;  
    node *last;
};

bool compareSym(sym a, sym b)
{
    return (a.type == b.type && strcmp(a.name, b.name)==0 && a.pos == b.pos);
}
