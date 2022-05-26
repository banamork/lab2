#include <stdlib.h>
#include <stdio.h>
#include "stack.h"


struct stack* CreateStack(int setCapacity)
{
    struct stack* ownStack = (struct stack *)calloc(1, sizeof(struct stack));
#ifdef VECTOR_IMPELEMENTATION
    ownStack->capacity = setCapacity;
    ownStack->vector = (int *)calloc(setCapacity, sizeof(int));
    ownStack->size = 0;
    return ownStack;
#endif

#ifdef LIST_IMPLEMENTATION
    ownStack->size = 0;
    return ownStack;
#endif
    return  NULL;
}

int Push(int setData, struct stack* ownStack)
{
#ifdef LIST_IMPLEMENTATION
    if(ownStack == NULL)
    {
        return ERROR;
    }

    struct item* node = (struct item *)calloc(1, sizeof(struct item));
    node->data = setData;

    if(ownStack->size == 0)
    {
        ownStack->head = node;
        ownStack->size = 1;
        return SUCCES;
    }

    else
    {
        node->next = ownStack->head;
        ownStack->head = node;
        ownStack->size++;
        return SUCCES;
    }
#endif

#ifdef VECTOR_IMPELEMENTATION
    if(ownStack->size >= ownStack->capacity) return ERROR;


    ownStack->vector[ownStack->size] = setData;
    ownStack->size++;

    return SUCCES;
#endif
    return ERROR;
}


int Pop(int *returnData, struct stack* ownStack) {
#ifdef LIST_IMPLEMENTATION
    if(ownStack == NULL || ownStack->head == NULL)
    {
        return ERROR;
    }

    *returnData = ownStack->head->data;
    ownStack->size--;

    if(ownStack->head->next != NULL)
    {
        struct item* current = ownStack->head;
        ownStack->head = ownStack->head->next;
        free(current);
    }
    else{
        free(ownStack->head);
        ownStack->head = NULL;
    }
    return SUCCES;
#endif

#ifdef VECTOR_IMPELEMENTATION
    if (ownStack->size == 0) {
        return ERROR;
    }


    ownStack->size--;
    *returnData = ownStack->vector[ownStack->size];


    return SUCCES;
#endif
    return  ERROR;
}

void freeStack(struct stack* ownStack)
{
#ifdef LIST_IMPLEMENTATION
    if(ownStack == NULL || ownStack->head == NULL)
    {
        free(ownStack);
        return;
    }



    while(ownStack->head != NULL)
    {
        struct item* previous = ownStack->head;
        ownStack->head = ownStack->head->next;
        free(previous);
    }

    free(ownStack);
    return;
#endif

#ifdef VECTOR_IMPELEMENTATION
    free(ownStack->vector);
    free(ownStack);
    return;
#endif



}




