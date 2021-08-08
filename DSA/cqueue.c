/*
 * Circular Implementation in C
 * improved version of queue
 * 
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#define N 6
typedef struct CQueue
{
    int top, rear, key[N];
} CQ;
void InitialiseCQueue(CQ *ptr)
{
    ptr->top = -1;
    ptr->rear = -1;
}
int SizeCQueue(CQ *ptr)
{
    if (ptr->top == -1)
        return 0;
    else if ((ptr->top != -1) && (ptr->top == ptr->rear))
        return 1;
    else if (ptr->top == ptr->rear + 1) //CQueue
        return N;
    else
        return ((ptr->rear) - (ptr->top) + 1);
}
int IsEmpty(CQ *ptr)
{
    if (SizeCQueue(ptr) == 0)
        return 1;
    else
        return 0;
}
int IsFull(CQ *ptr)
{
    if (SizeCQueue(ptr) == N)
        return 1;
    else
        return 0;
}
void EnQueue(CQ *ptr, int num)
{
    if (IsFull(ptr))
        printf("\nCQueue is Full...\n");
    else
    {
        if (IsEmpty(ptr))
        {
            ptr->rear = 0;
            ptr->top = 0;
        }
        else if (ptr->rear + 1 == N) //CQueue comes into play
            ptr->rear = 0;
        else
            ptr->rear++;
        ptr->key[ptr->rear] = num;
    }
}
void DeQueue(CQ *ptr)
{
    if (IsEmpty(ptr))
        printf("\nCQueue is Empty...\n");
    else
    {
        if (SizeCQueue(ptr) == 1)
        {
            ptr->top = -1;
            ptr->rear = -1;
        }
        else
            ptr->top++;
    }
}
void PrintCQueue(CQ *ptr)
{
    if (ptr->rear >= ptr->top)
        for (int i = ptr->rear; i >= ptr->top; i--) //prints in reverse order
            printf("%d  ", ptr->key[i]);
    else
    {
        for (int i = N - 1; i >= ptr->top; i--)
            printf("%d ", ptr->key[i]);
        printf("\t");
        for (int i = ptr->rear; i >= 0; i--)
            printf("%d ", ptr->key[i]);
    }
    printf("\n");
}
void main(void)
{
    CQ *ptr;
    ptr = (CQ *)malloc(sizeof(CQ *));
    InitialiseCQueue(ptr);
    EnQueue(ptr, 1);
    EnQueue(ptr, 2);
    EnQueue(ptr, 3);
    printf("\ntop=%d\trear=%d\n", ptr->top, ptr->rear);
    PrintCQueue(ptr);
    EnQueue(ptr, 4);
    EnQueue(ptr, 5);
    EnQueue(ptr, 6);
    PrintCQueue(ptr);
    printf("%d%d\n", IsFull(ptr), IsEmpty(ptr));
    EnQueue(ptr, 7);
    PrintCQueue(ptr);
    DeQueue(ptr);
    printf("\ntop=%d\trear=%d\n", ptr->top, ptr->rear);
    DeQueue(ptr);
    PrintCQueue(ptr);
    DeQueue(ptr);
    DeQueue(ptr);
    printf("%d%d\n", IsFull(ptr), IsEmpty(ptr));
    printf("\ntop=%d\trear=%d\n", ptr->top, ptr->rear);
    DeQueue(ptr);
    PrintCQueue(ptr);
    EnQueue(ptr, 8);
    EnQueue(ptr, 9);
    printf("\ntop=%d\trear=%d\n", ptr->top, ptr->rear);
    EnQueue(ptr, 10);
    PrintCQueue(ptr);
    EnQueue(ptr, 11);
    EnQueue(ptr, 12);
    printf("%d%d\n", IsFull(ptr), IsEmpty(ptr));
    EnQueue(ptr, 13);
    printf("\ntop=%d\trear=%d\n", ptr->top, ptr->rear);
    free(ptr);
}