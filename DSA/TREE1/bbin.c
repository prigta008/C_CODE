#include <stdio.h>
#include <stdlib.h>
#include <math.h>
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
int isBalancedTree(struct Node *node, int *height)
{
    int lh = 0, rh = 0, l = 0, r = 0;
    if (node == NULL)
    {
        *height = 0;
        return 1;
    }
    l = isBalancedTree(node->left, &lh);
    r = isBalancedTree(node->right, &rh);
    *height = (lh > rh ? lh : rh) + 1;
    if (abs(lh - rh) >= 2)
        return 0;
    else
        return l && r;
}
void main()
{
    struct Node *parent = create(1);
    insert(parent, 2, 0);
    insert(parent, 3, 1);
    insert(parent->left, 4, 0);
    insert(parent->left, 5, 1);
    insert(parent->left->right, 7, 1);
    int height = 0;
    if (isBalancedTree(parent, &height))
        printf("Balanced");
    else
        printf("Unbalanced");
}