#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include "stack.h"


void print_vector(int *vector, int size)
{
    for(int i = 0; i < size; i ++)
    {
        printf("%d", vector[i]);
    }
    printf("\n");
}

int operation(struct stack *ownStack, char sign, int *result);

enum Status
{
    Plus = 1,
    Minus = 2,
    Multi = 3,
    Div = 4,
};

int main() {
    int size = 0;

#ifdef VECTOR_IMPELEMENTATION
    printf("Please input stack size\n");
    scanf("%d", &size);
    int elements_counter = 0;
#endif



    struct stack *s;
    s = CreateStack(size);

    char *inputedString = NULL;
    inputedString = readline("Please input expression:\n");
    char *token = strtok(inputedString, " ");
    int number = atoi(token);

    Push(number, s);

    int result = 0;
    char sign;

    while(token != NULL)
    {
        token = strtok(NULL, " ");
        if(token != NULL)
        {

            if(*token == '+' || *token == '-' || *token == '*' || *token == '/')
            {
                sign = *token;

                if(operation(s, sign, &result) == ERROR)
                {
#ifdef VECTOR_IMPELEMENTATION
                    printf("Underflow\n");
#endif
                    free(inputedString);
                    freeStack(s);
                    return 0;
                }
            }

            else
            {
                if(atoi(token)) {
                    int number = atoi(token);
#ifdef VECTOR_IMPELEMENTATION
                    elements_counter++;
                    if(elements_counter >= size)
                    {
                        printf("Overflow\n");
                        free(inputedString);
                        freeStack(s);
                        return 0;
                    }
#endif
                    Push(number, s);
                }
                else
                {
                    printf("Incorrect input\n");
                    freeStack(s);
                    free(inputedString);
                    return 0;
                }

            }
        }
    }


    if(s->size > 1)
    {
        printf("Incorrect sign input\n");
    }
    else {
        Pop(&result, s);
        printf("Result is: %d\n", result);
    }

    freeStack(s);
    free(inputedString);
    return 0;

}
int operation(struct stack *ownStack, char sign, int *result)
{
    int status = 0;
    if(sign == '+') status = Plus;
    else if(sign == '-') status = Minus;
    else if(sign == '*') status = Multi;
    else if(sign == '/') status = Div;
    int a, b;
    if(Pop(&a, ownStack) == -1) return ERROR;
    if(Pop(&b, ownStack) == -1) return ERROR;


    switch(status)
    {
        case Plus:
            Push(a + b, ownStack);
            return SUCCES;

        case Minus:
            Push(a - b, ownStack);
            return SUCCES;

        case Multi:
            Push(a * b, ownStack);
            return SUCCES;

        case Div:
            if(b != 0)
            Push(a / b, ownStack);
            return SUCCES;

        default:
            printf("Unknown error\n");
            return ERROR;

    }
}
