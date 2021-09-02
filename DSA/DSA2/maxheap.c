#include <stdio.h>
#include <stdlib.h>
#define SIZE 11
int array[SIZE], size = 0;
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}
void heapify(int i)
{
    int leftchild = 2 * i + 1,
        rightChild = 2 * i + 2,
        largest = i;
    if (leftchild < size && array[leftchild] > array[i])         //if leftchild exists and leftchild is greater than parent
        largest = leftchild;                                     //largest becomes leftchild
    if (rightChild < size && array[rightChild] > array[largest]) //if rightchild exists and rightchild is greater than previous largest
        largest = rightChild;                                    //largest becomes rightchild
    if (largest != i)
    {
        swap(&array[i], &array[largest]);
        heapify(largest);
    }
}
void insert(int n)
{
    if (size == SIZE) //array is full
        printf("heap is full\n");
    else
    {
        array[size] = n;
        size++;
        for (int i = (size / 2) - 1; i >= 0; i--)
            heapify(i);
    }
}
void delete (int n)
{
    int i, c = 0;
    for (i = 0; i < size; i++)
        if (array[i] == n)
        {
            c = 1;
            break;
        }
    if (c == 0)
        printf("\nDoesn't exist\n");
    else
    {                                             //if found
        swap(&array[i], &array[size - 1]);        //swap with last element
        size--;                                   //remove the last element
        for (int j = (size / 2) - 1; j >= 0; j--) //heapify
            heapify(j);
    }
}
void print()
{
    printf("Array : ");
    for (int i = 0; i < size; i++)
        printf("%d ", array[i]);
    printf("\n");
}
void main()
{
    int choice, value;
    do
    {
        printf("Menu :\n"
               "1. Insert data\n"
               "2. Delete data\n"
               "3. Print array\n"
               "4. Exit\n"
               " Enter your choice : ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            printf("Enter the number : ");
            scanf("%d", &value);
            insert(value);
            break;
        case 2:
            printf("Enter the number you want to delete : ");
            scanf("%d", &value);
            delete (value);
            break;
        case 3:
            print();
            break;
        default:
            break;
        }
    } while (choice < 4);
}