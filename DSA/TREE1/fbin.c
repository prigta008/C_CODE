/*
 *  Full Binary Tree
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
int isFullBinaryTree(struct Node *node)
{
    if (node == NULL)
        return 1;
    else if (node->left == NULL && node->right == NULL)
        return 1;
    else if (node->left != NULL && node->right != NULL)
        return isFullBinaryTree(node->left) && isFullBinaryTree(node->right);
    else
        return 0;
}
void main()
{
    struct Node *parent = create(1);
    insert(parent, 2, 0);
    insert(parent, 3, 1);
    insert(parent->left, 4, 0);
    insert(parent->left, 5, 1);
    insert(parent->left->right, 6, 0);
    insert(parent->left->right, 7, 1);
    if (isFullBinaryTree(parent))
        printf("it is a full binary tree");
    else
        printf("it is not a full binary tree");
}