#include <stdio.h>
#include <stdlib.h>
#define N 8
typedef struct DQueue
{
    int front, rear, key[N];
} DQ;
void initialize(DQ *ptr)
{
    ptr->front = -1;
    ptr->rear = -1;
    for (int i = 0; i < N; i++)
        ptr->key[i] = 0;
}
int Size(DQ *ptr)
{
    int l = 0, i;
    for (i = 0; i < N; i++)
        if (ptr->key[i] != 0)
            l++;
    return l;
}
int isempty(DQ *ptr)
{
    if (Size(ptr) == 0)
        return 1;
    else
        return 0;
}
int isfull(DQ *ptr)
{
    if (Size(ptr) == N)
        return 1;
    else
        return 0;
}
void insertfromfront(DQ *ptr, int num)
{
    if (isfull(ptr))
        printf("\nQueue is full\n");
    else
    {
        if (isempty(ptr))
        {
            ptr->front = ptr->rear = 0;
            ptr->key[ptr->front] = num;
        }
        else
        {
            for (int k = (ptr->rear) + 1; k > 0; k--)
                ptr->key[k] = ptr->key[k - 1];
            ptr->key[0] = num;
            ptr->rear++;
        }
    }
}
void insertfromrear(DQ *ptr, int num)
{
    if (isfull(ptr))
        printf("\nQueue is full\n");
    else
    {
        ptr->rear++;
        ptr->key[ptr->rear] = num;
    }
}
void deletefromfront(DQ *ptr)
{
    if (isempty(ptr))
        printf("\nQueue is empty\n");
    else
    {
        ptr->key[ptr->front] = 0;
        if (Size(ptr) == 1)
            ptr->front = ptr->rear = -1;
        else
            ptr->front++;
    }
}
void deletefromrear(DQ *ptr)
{
    if (isempty(ptr))
        printf("\nQueue is empty\n");
    else
    {
        ptr->key[ptr->rear] = 0;
        ptr->rear--;
    }
}
void display(DQ *ptr)
{
    for (int i = 0; i < N; i++)
        printf("%d ", ptr->key[i]);
    printf("\n");
}
void main()
{
    DQ *ptr = (DQ *)malloc(sizeof(DQ *));
    initialize(ptr);
    int n, num;
    do
    {
        printf("\nMenu :\n1.Insert from front.\n2.Insert from rear.\n3.Delete from front.\n4.Delete from rear\n5.Display.\n6.Count.\n7.Exit.\n Enter your choice : ");
        scanf("%d", &n);
        switch (n)
        {
        case 1:
            printf("Enter integer  : ");
            scanf("%d", &num);
            insertfromfront(ptr, num);
            break;
        case 2:
            printf("Enter integer  : ");
            scanf("%d", &num);
            insertfromrear(ptr, num);
            break;
        case 3:
            deletefromfront(ptr);
            break;
        case 4:
            deletefromrear(ptr);
            break;
        case 5:
            display(ptr);
            break;
        case 6:
            printf("Size : %d\n", Size(ptr));
            break;
        default:
            break;
        }
    } while (n < 7);
    free(ptr);
}