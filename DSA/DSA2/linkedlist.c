#include <stdio.h>
#include <stdlib.h>
struct Node
{
    int data;
    struct Node *next;
};
void printlist(struct Node *ptr)
{
    printf("Linked List : ");
    while (ptr != NULL)
    {
        printf(" | %d | ", ptr->data);
        ptr = ptr->next;
    }
    printf("\n");
}
void addatbegin(struct Node **head, int num)
{
    struct Node *ptr = (struct Node *)malloc(sizeof(struct Node));
    ptr->data = num;
    ptr->next = *head;
    *head = ptr;
}
void addinbetween(struct Node *head, int clue, int num)
{
    struct Node *ptr = (struct Node *)malloc(sizeof(struct Node));
    ptr->data = num;
    while (head != NULL)
    {
        if (head->data == clue)
            break;
        head = head->next;
    }
    if (head == NULL)
        return; //not found
    else
    {
        ptr->next = head->next;
        head->next = ptr;
    }
}
void addatlast(struct Node *head, int num)
{
    struct Node *ptr = (struct Node *)malloc(sizeof(struct Node));
    ptr->data = num;
    ptr->next = NULL;
    while (head->next != NULL)
        head = head->next;
    head->next = ptr;
}
void deletenode(struct Node *head, int clue)
{
    if (head->data == clue)
        return;
    else
    {
        while (head != NULL)
        { //I think first node cannot be deleted
            if (head->next->data == clue)
                break;
            head = head->next;
        }
        if (head == NULL)
            return;
        else
            head->next = head->next->next;
    }
}
int search(struct Node *head, int item)
{
    int c = 0;
    while (head != NULL)
    {
        if (head->data == item)
            c = 1;
        head = head->next;
    }
    return c;
}
void sortlist(struct Node *head)
{
    struct Node *ptr = (struct Node *)malloc(sizeof(struct Node));
    int temp;
    while (head->next != NULL)
    {
        ptr = head;
        while (ptr->next != NULL)
        {
            if (ptr->data > ptr->next->data)
            {
                temp = ptr->data;
                ptr->data = ptr->next->data;
                ptr->next->data = temp;
            }
            ptr = ptr->next;
        }
        head = head->next;
    }
}
void main()
{
    struct Node *head = (struct Node *)malloc(sizeof(struct Node));
    int choice, num, clue;
    head->data = 5;
    head->next = NULL;
    do
    {
        printf("Menu :\n1.insert at begininning.\n2.insert in between.\n3.insert at last.\n4.delete a node.\n5.search a node.\n6.sort the list.\n7.exit\n Enter your choice : ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            printf("Enter the number : ");
            scanf("%d", &num);
            addatbegin(&head, num);
            printlist(head);
            break;
        case 2:
            printf("Enter the number as data of that node after you want to add node : ");
            scanf("%d", &clue);
            printf("Enter the number : ");
            scanf("%d", &num);
            addinbetween(head, clue, num);
            printlist(head);
            break;
        case 3:
            printf("Enter the number : ");
            scanf("%d", &num);
            addatlast(head, num);
            printlist(head);
            break;
        case 4:
            printf("Enter the number as data of that node you want to delete : ");
            scanf("%d", &clue);
            deletenode(head, clue);
            printlist(head);
            break;
        case 5:
            printf("Enter the number : ");
            scanf("%d", &clue);
            if (search(head, clue))
                printf("%d is found\n", clue);
            else
                printf("%d is not found\n", clue);
            break;
        case 6:
            sortlist(head);
            printlist(head);
            break;
        default:
            break;
        }
    } while (choice < 7);
}