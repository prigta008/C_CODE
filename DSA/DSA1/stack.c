/*
 * Stack Implementation In C
 */
#include <stdio.h>
#include <stdlib.h>
#define N 9
typedef struct Stack
{
    int key[N], top;
} st;
int IsEmpty(st *ptr)
{
    if (ptr->top == -1)
        return 1;
    else
        return 0;
}
int IsFull(st *ptr)
{
    if (ptr->top == N - 1)
        return 1;
    else
        return 0;
}
void InitializeStack(st *ptr)
{
    ptr->top = -1;
}
void PushInStack(st *ptr, int num)
{
    if (IsFull(ptr))
        printf("\nStack is full\n");
    else
    {
        ptr->top++;
        ptr->key[ptr->top] = num;
    }
}
void PopInStack(st *ptr)
{
    if (IsEmpty(ptr))
        printf("\nStack is Empty\n");
    else
        ptr->top--;
}
int PeekInStack(st *ptr)
{
    if (IsEmpty(ptr))
        printf("\nStack is Empty\n");
    else
        return ptr->key[ptr->top];
}
void PrintStack(st *ptr)
{
    if (IsEmpty(ptr))
        printf("\nStack is empty\n");
    for (int i = 0; i <= ptr->top; i++)
        printf("%d  ", ptr->key[i]);
    printf("\n");
}
void main()
{
    st *ptr;
    ptr = (st *)malloc(sizeof(st *));
    int n;
    InitializeStack(ptr); //initialising stack
    PushInStack(ptr, 1);  //adding 1 *last in*
    PushInStack(ptr, 2);  //adding 2 *last in*
    PushInStack(ptr, 4);  //adding 4 *last in*
    PushInStack(ptr, 10); //adding 10 *last in*
    PrintStack(ptr);      //priniting value to check for any error
    PushInStack(ptr, 87); //adding 87 *last in*
    PrintStack(ptr);      //printing again
    PopInStack(ptr);      //popping *last out*
    PrintStack(ptr);      //checking again
    PopInStack(ptr);      //popping
    PrintStack(ptr);
    printf("%d\n%d", IsFull(ptr), IsEmpty(ptr)); //checking for full and empty
    printf("\n%d\n", PeekInStack(ptr));          //peeking
    PushInStack(ptr, 23);
    PushInStack(ptr, 45);
    PushInStack(ptr, 23);
    PushInStack(ptr, 67);
    PushInStack(ptr, 56);
    PushInStack(ptr, 7);                         //stack should be full now.
    printf("%d\n%d", IsFull(ptr), IsEmpty(ptr)); //checking for full and empty
    PushInStack(ptr, 3);                         //error should occur
    PopInStack(ptr);
    PopInStack(ptr);
    PopInStack(ptr);
    PopInStack(ptr);
    PopInStack(ptr);
    PopInStack(ptr);
    PopInStack(ptr);
    PopInStack(ptr);
    PrintStack(ptr); //only 1 item is left
    PopInStack(ptr); //stack should be empty now
    PopInStack(ptr); //error should occur
                     /*
                        I think Everything is done
                      */
    free(ptr);       //free the pointer.
}