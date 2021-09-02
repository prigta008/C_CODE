/*
 * Perfect Binary Tree
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
    struct Node *new = (struct Node *)malloc(sizeof(struct Node));
    new->data = data;
    new->left = new->right = NULL;
    return new;
}
void insert(struct Node *parent, int data, int side)
{
    if (side)
        parent->right = create(data);
    else
        parent->left = create(data);
}
int calculate(struct Node *node)
{
    int d = 0;
    while (node != NULL)
    {
        d++;
        node = node->left;
    }
    return d;
}
int isPerfectBinaryTree(struct Node *node, int d, int level)
{
    if (node == NULL)
        return 1;
    else if (node->left == NULL && node->right == NULL)
        return (d == level + 1);
    else if (node->left == NULL || node->right == NULL)
        return 0;
    else
        return isPerfectBinaryTree(node->left, d, level + 1) && isPerfectBinaryTree(node->right, d, level + 1);
}
void main()
{
    struct Node *parent = create(1);
    insert(parent, 2, 0);
    insert(parent, 3, 1);
    insert(parent->left, 4, 0);
    insert(parent->left, 5, 1);
    //  insert(parent->right, 6, 0);
    // insert(parent->right, 7, 1);
    if (isPerfectBinaryTree(parent, calculate(parent), 0))
        printf("it is a perfect binary tree");
    else
        printf("it is not a perfect binary tree");
}