/*
 * Queue Implementation in C, works on FIFO rule
 *
 *  Queue : 
 *    Index: 3 2 1 0 
 *      In ↪ 5 3 2 1 ↪ Out 
 */

#include <stdio.h>
#include <stdlib.h>
#define N 6
typedef struct Queue
{
    int top, rear, key[N];
} Q;
void InitializeQueue(Q *ptr)
{
    ptr->top = -1;
    ptr->rear = -1;
}
int SizeOfQueue(Q *ptr)
{
    if (((ptr->top) == 0) && ((ptr->rear) == 0))
        return 1;
    else if (ptr->top == -1)
        return 0;
    else
        return ((ptr->rear) - (ptr->top) + 1);
}
int IsFull(Q *ptr)
{
    if (SizeOfQueue(ptr) == N)
        return 1;
    else
        return 0;
}
int IsEmpty(Q *ptr)
{
    if (SizeOfQueue(ptr) == 0)
        return 1;
    else
        return 0;
}
void EnQueue(Q *ptr, int num)
{
    if (IsFull(ptr))
        printf("\nQueue is Full\n");
    else
    {
        if (IsEmpty(ptr))
        {
            ptr->top = 0;
            ptr->rear = 0;
        }
        else
            ptr->rear++;
        ptr->key[ptr->rear] = num;
    }
}
void DeQueue(Q *ptr)
{
    if (IsEmpty(ptr))
        printf("\nQueue is Empty...\n");
    if (SizeOfQueue(ptr) == 1)
    {
        ptr->rear = -1;
        ptr->top = -1;
    }
    else
        ptr->top++;
}
void PrintQueue(Q *ptr)
{
    for (int i = ptr->rear; i >= ptr->top; i--)//prints in reverse order 
        printf("%d  ", ptr->key[i]);
    printf("\n");
}
void main(void)
{
    Q *ptr;
    ptr = (Q *)malloc(sizeof(Q *));
    InitializeQueue(ptr);// Queue is now : 
    EnQueue(ptr, 1); //                          1
    EnQueue(ptr, 2);//                         2 1
    EnQueue(ptr, 3);//                       3 2 1
    EnQueue(ptr, 5);//                     5 3 2 1
    PrintQueue(ptr);//output : 5 3 2 1
    DeQueue(ptr);//                        5 3 2
    PrintQueue(ptr);//output : 5 3 2
    EnQueue(ptr, 6);//                   6 5 3 2
    printf("%d\n", SizeOfQueue(ptr));
    EnQueue(ptr, 7);//                 7 6 5 3 2
    EnQueue(ptr, 6);//               6 7 6 5 3 2
    //q is full
    EnQueue(ptr, 8);// output : queue is full
    printf("%d", SizeOfQueue(ptr));// output : 6
    DeQueue(ptr);//                  6 7 6 5 3 
    DeQueue(ptr);//                  6 7 6 5
    DeQueue(ptr);//                  6 7 6
    printf("\n%d\t%d\n", IsFull(ptr), IsEmpty(ptr));// output : 0 0
    DeQueue(ptr);//                  6 7
    DeQueue(ptr);//                  6
    //printing value of top and rear :: limitation of Queue
    printf("\ntop=%d\trear=%d\n", ptr->top, ptr->rear);//output : top=6 rear=6
    PrintQueue(ptr);//               6
    printf("%d", SizeOfQueue(ptr));//output : 1
    DeQueue(ptr); //empty
    printf("\ntop=%d\trear=%d\n", ptr->top, ptr->rear);//output : top=-1    rear=-1
    DeQueue(ptr);//output : Queue is empty
    free(ptr);
}