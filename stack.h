#ifndef STACK_H
#define STACK_H
#define LIST_IMPLEMENTATION
//#define VECTOR_IMPELEMENTATION


enum ReturnCode
{
    SUCCES = 0,
    ERROR = -1

};
#ifdef LIST_IMPLEMENTATION
struct item
{
    int data;
    struct item* next;
};
#endif

struct stack
{
    int size;

#ifdef LIST_IMPLEMENTATION
    struct item* head;
#endif

#ifdef VECTOR_IMPELEMENTATION
    int *vector;
    int capacity;
#endif
};

int Pop(int *returnData, struct stack* ownStack);
struct stack* CreateStack(int capacity);
int Push(int setData, struct stack* ownStack);
void freeStack(struct stack* ownStack);

#endif