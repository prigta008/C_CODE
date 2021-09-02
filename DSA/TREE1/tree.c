#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
struct Node
{
    int data;
    struct Node *left, *right;
};
void inorder(struct Node *node), preorder(struct Node *node), postorder(struct Node *node);
void inorder(struct Node *node)
{
    if (node)
    {
        inorder(node->left);
        printf("%d ", node->data);
        inorder(node->right);
    }
}
void preorder(struct Node *node)
{
    if (node)
    {
        printf("%d ", node->data);
        preorder(node->left);
        preorder(node->right);
    }
}
void postorder(struct Node *node)
{
    if (node)
    {
        postorder(node->left);
        postorder(node->right);
        printf("%d ", node->data);
    }
}
struct Node *create(int value)
{
    struct Node *node = (struct Node *)malloc(sizeof(struct Node));
    node->data = value;
    node->left = node->right = NULL;
    return node;
}
void insert(struct Node *parent, int value, int side)
{
    if (side)
        parent->right = create(value);
    else
        parent->left = create(value);
}
void main()
{
    struct Node *parent = create(1);
    insert(parent, 2, 0);
    insert(parent, 3, 1);
    insert(parent->left, 4, 0);
    insert(parent->left, 7, 1);
    printf("\nInorder : ");
    inorder(parent);
    printf("\nPreOrdre : ");
    preorder(parent);
    printf("\nPostOrdre : ");
    postorder(parent);
}