#include <stdio.h>
#define V 5
// entries 0 to 5
//undirected graph
void init(int arr[V][V])
{
    for (int i = 0; i < V; i++)
        for (int j = 0; j < V; j++)
            arr[i][j] = 0;
}
void addedge(int arr[V][V], int i, int j)
{
    arr[i][j] = arr[j][i] = 1;
}
void printarr(int arr[V][V])
{
    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
            printf("%d ", arr[i][j]);
        printf("\n");
    }
    printf("\n");
}
void main()
{
    int arr[V][V];
    init(arr);
    addedge(arr, 0, 4);
    addedge(arr, 3, 4);
    addedge(arr, 1, 3);
    addedge(arr, 2, 3);
    addedge(arr, 1, 2);
    printarr(arr);
}