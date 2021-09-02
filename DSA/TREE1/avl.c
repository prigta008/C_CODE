/*
 * AVL tree
 */
#include <stdio.h>
#include <stdlib.h>
struct Node
{
    int data, height;
    struct Node *left, *right;
};
int max(int a, int b)
{
    return a > b ? a : b;
}
int height(struct Node *node)
{
    if (node == NULL)
        return 0;
    else
        return node->height;
}
int getBalance(struct Node *node)
{
    if (node == NULL)
        return 0;
    else
        return (height(node->left) - height(node->right));
}
struct Node *create(int data)
{
    struct Node *new = (struct Node *)malloc(sizeof(struct Node));
    new->data = data;
    new->left = new->right = NULL;
    new->height = 1;
    return new;
}
struct Node *rightrotate(struct Node *y)
{ //y is the node where rotation happens
    if (y->left == NULL || y->left->right == NULL)
        return y;
    else
    {
        struct Node *x = y->left, *beta = x->right;
        x->right = y;
        y->left = beta;
        x->height = max(height(x->left), height(x->right)) + 1;
        y->height = max(height(y->left), height(y->right)) + 1;
        return x;
    }
}
struct Node *leftrotate(struct Node *x)
{
    if (x->right == NULL || x->right->left == NULL)
        return x;
    else
    {
        struct Node *y = x->right, *beta = y->left;
        y->left = x;
        x->right = beta;
        x->height = max(height(x->left), height(x->right)) + 1;
        y->height = max(height(y->left), height(y->right)) + 1;
        return y;
    }
}
struct Node *insert(struct Node *node, int data)
{
    //insert node
    if (node == NULL)
        return create(data);
    if (data > node->data)
        node->right = insert(node->right, data);
    else
        node->left = insert(node->left, data);

    //update height/balance factor
    node->height = max(height(node->left), height(node->right)) + 1;
    int height = getBalance(node);
    if (height > 1 && data < node->left->data)
        return rightrotate(node);
    if (height < -1 && data > node->right->data)
        return leftrotate(node);
    if (height > 1 && data > node->left->data)
    {
        node->left = leftrotate(node);
        return rightrotate(node);
    }
    if (height < -1 && data < node->right->data)
    {
        node->right = rightrotate(node);
        return leftrotate(node);
    }
    else
        return node;
}
struct Node *minsuc(struct Node *node)
{
    while (node && node->left != NULL)
        node = node->left;
    return node;
}
struct Node *deletenode(struct Node *node, int data)
{
    if (data > node->data)
        node->right = deletenode(node->right, data);
    else if (data < node->data)
        node->left = deletenode(node->left, data);
    else
    { //if match
        if (node->left == NULL && node->right == NULL)
            return NULL;
        if (node->left != NULL && node->right != NULL)
        { //2 child
            struct Node *temp = (struct Node *)malloc(sizeof(struct Node));
            temp->left = node->left;
            temp->data = minsuc(node->right)->data;
            temp->right = deletenode(node->right, minsuc(node->right)->data);
            return temp; //updated
        }
        else
        { //single child
            if (node->left != NULL)
                return node->left;
            else
                return node->right;
        }
    }
    //update height
    node->height = max(height(node->left), height(node->right)) + 1;
    int height = getBalance(node);
    if (height > 1 && getBalance(node->left) >= 0)
        return rightrotate(node);
    if (height > 1 && getBalance(node->left) < 0)
    {
        node->left = leftrotate(node->left);
        return rightrotate(node);
    }
    if (height < -1 && getBalance(node->right) >= 0)
        return leftrotate(node);
    if (height < -1 && getBalance(node->right) < 0)
    {
        node->right = rightrotate(node->right);
        return leftrotate(node);
    }
    else
        return node;
}
void inorder(struct Node *node)
{
    if (node != NULL)
    {
        inorder(node->left);
        printf("%d  ", node->data);
        inorder(node->right);
    }
}
int search(struct Node *parent, int data)
{
    if (parent != NULL)
    {
        if (parent->data == data) //found case
            return 1;
        else if (parent->data > data)
            search(parent->left, data);
        else if (parent->data < data)
            search(parent->right, data);
    }
    else //not found case
        return 0;
}
void main()
{
    struct Node *parent = create(33);
    insert(parent, 13);
    insert(parent, 53);
    insert(parent, 11);
    insert(parent, 21);
    insert(parent, 61);
    insert(parent, 8);
    insert(parent, 9);
    printf("Inorder : ");
    inorder(parent); //gives answer in ascending order
}