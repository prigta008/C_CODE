/*
 * Binary Search Tree
 */
#include <stdlib.h>
#include <stdio.h>
struct Node
{
    int data;
    struct Node *left, *right;
};
struct Node *minsuc(struct Node *node)
{
    while (node && node->left != NULL)
        node = node->left;
    return node;
}
struct Node *create(int data)
{
    struct Node *new = (struct Node *)malloc(sizeof(struct Node));
    new->data = data;
    new->left = new->right = NULL;
    return new;
}
struct Node *insert(struct Node *parent, int data)
{
    if (parent == NULL)
        return create(data);
    else if (parent->data > data)
        parent->left = insert(parent->left, data);
    else
        parent->right = insert(parent->right, data);
    return parent;
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
        {
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
}
void inorder(struct Node *parent)
{
    if (parent != NULL)
    {
        inorder(parent->left);
        printf("%d ", parent->data);
        inorder(parent->right);
    }
}
void main()
{
    struct Node *parent = create(8);
    insert(parent, 3);
    insert(parent, 10);
    insert(parent, 1);
    insert(parent, 6);
    insert(parent, 4);
    printf("Inorder : ");
    inorder(parent);
 parent=   deletenode(parent, 8);
    printf("\nInorder : ");
    inorder(parent);
    printf("\n 6 found : %d ; 0 means not; 1 means yes", search(parent, 6));
    printf("\n 4 found : %d ; 0 means not; 1 means yes", search(parent, 4));
}