#include <stdio.h>
#include "structs.c"
#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>

/*
 * Para ver el proceso en la pila puede decomentar los printf en las
 * funciones push y pop.
 */

bool is_empty(stack *stack)
{
    assert(stack != NULL);
    return (stack->last == NULL);
}

void push(stack* stack, sym* info)
{
    assert(stack != NULL && info != NULL);
    node* newNode = (node*)malloc(sizeof(node));
    newNode->previous = stack->last;
    newNode->info = *info;
    
    if(is_empty(stack)){
        stack->first = newNode;
    }
    
    stack->last = newNode;
    //printf("mete: %s \n",info->name);
}

void pop(stack* stack)
{
    assert(stack != NULL);
    
    if(!is_empty(stack)){
        node *newNode = (node*)malloc(sizeof(node));
        newNode = stack->last;
        stack->last = newNode->previous;
        //printf("saca: %s \n",newNode->info.name);
        free(newNode);
    }
}

sym top(stack* stack)
{
    return stack -> last -> info;
}

stack* newStack()
{
    stack* stack = malloc(sizeof(stack));
    stack->first = NULL;
    stack->last = NULL;
    
    return stack; 
}

