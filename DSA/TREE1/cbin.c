/*
 * Complete Binary Tree
 */
#include <stdio.h>
#include <stdlib.h>
struct Node
{
    int data;
    struct Node *left, *right;
};
struct Node *create(int data)
{
    struct Node *newnode = (struct Node *)malloc(sizeof(struct Node));
    newnode->data = data;
    newnode->left = newnode->right = NULL;
    return newnode;
}
void insert(struct Node *parent, int data, int side)
{
    if (side)
        parent->right = create(data);
    else
        parent->left = create(data);
}
int count(struct Node *parent)
{
    if (parent == NULL)
        return 0;
    else
        return (1 + count(parent->left) + count(parent->right));
}
int isComplete(struct Node *parent, int index, int nodes)
{
    if (parent == NULL)
        return 1;
    else if (index >= nodes)
        return 0;
    else
        return (isComplete(parent->left, 2 * index + 1, nodes) && isComplete(parent->right, 2 * index + 2, nodes));
}
void main()
{
    struct Node *parent = create(1);
    insert(parent, 2, 0);
    insert(parent, 3, 1);
    insert(parent->left, 4, 0);
    insert(parent->left, 5, 1);
    insert(parent->right, 6, 0);//change rightmost 0 with 1 and check the output
    if (isComplete(parent, 0, count(parent)))
        printf("It is a complete binary tree");
    else
        printf("it is not a complete binary tree");
}