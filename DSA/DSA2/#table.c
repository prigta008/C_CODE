#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define SIZE 8
struct Set
{
    int key, value;
};
struct Set *arr;
int capacity = SIZE, size = 0;
int hashfn(int key)
{
    return (key % SIZE);
}
int checkPrime(int n)
{
    int c = 1, i; //1 means yes, 0 means no
    if (n >= 1)
        c = 0;
    for (i = 2; i <= sqrt(n); i++)
    {
        if (n % i == 0)
            c = 0;
        break;
    }
    return c;
}
int getPrime(int n)
{
    if (n % 2 == 0)
        n++;
    while (checkPrime(n) == 1)
        n += 2;
    return n;
}
void init()
{
    capacity = getPrime(capacity);
    arr = (struct Set *)malloc(capacity * sizeof(struct Set));
    for (int i = 0; i < capacity; i++)
    {
        arr[i].key = 0;
        arr[i].value = 0;
    }
}
void insert(int key, int value)
{
    int hash = hashfn(key);
    if (arr[hash].value == 0)
    { //empty slot
        arr[hash].value = value;
        arr[hash].key = key;
        size++;
    }
    else if (arr[hash].key == key) //update
        arr[hash].value = value;
    else //collision happens when index or hash becomes same but key is different
        printf("\nCollision...\n");
}
void deleteent(int key)
{
    int hash = hashfn(key);
    if (arr[hash].value == 0)
        printf("Doesn't exist\n");
    if (arr[hash].key == key)
    {
        arr[hash].value = 0;
        arr[hash].key = 0; //removed
        size--;
    }
}
void display()
{
    for (int i = 0; i < capacity; i++)
    {
        if (arr[i].value == 0)
            printf("empty\n");
        else
            printf("key : %d value : %d\n", arr[i].key, arr[i].value);
    }
    printf("\n");
}
void main()
{
    int choice, key, value;
    init();
    do
    {
        printf("Menu :\n"
               "1. insert\n"
               "2. delete\n"
               "3. check size\n"
               "4. print #table\n"
               "5. exit\n"
               "\n Enter your choice : ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            printf("Enter key and value separated by a space : ");
            scanf("%d %d", &key, &value);
            insert(key, value);
            break;
        case 2:
            printf("Enter the key : ");
            scanf("%d", &key);
            deleteent(key);
            break;
        case 3:
            printf("Size : %d\n", size);
            break;
        case 4:
            display();
            break;
        default:
            break;
        }
    } while (choice < 5);
}