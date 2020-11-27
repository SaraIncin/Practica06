#include <stdio.h>

#define TERM 1
#define NON_TERM 2
#define EPSILON 3
#define NUM_TERM 9
#define NUM_NON_TERM 7

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
    {9, "11/10", 2},
    {10, "5/11/10", 3},
    {10, "-1", 0},
    {11, "13/12", 2},
    {12, "13/12", 2},
    {12, "-1", 0},
    {13, "15/14", 2},
    {14, "6/14", 2},
    {14, "7/14", 2},
    {14, "8/14", 2},
    {14, "-1", 0},
    {15, "0/9/1", 3},
    {15, "2", 1},
    {15, "3", 1},
};

int ANALYSIS_TABLE[NUM_NON_TERM][NUM_TERM] = {
    {0, -1, 0, 0, -1, -1, -1, -1, -1},
    {-1, 2, -1, -1, 2, 1, -1, -1, -1},
    {3, -1, 3, 3, -1, -1, -1, -1, -1},
    {4, -1, 4, 4, -1, 5, -1, -1, -1},
    {-1, -1, -1, -1, -1, -1, 6, 6, 6},
    {10, -1, 10, 10, -1, -1, 7, 8, 9},
    {11, -1, 12, 13, -1, -1, -1, -1, -1},
};
