#include <stdio.h>
#include <stdlib.h>
#define NULL ((void *)0)
#define V 4
struct node
{
    int vertex;
    struct node *next;
};
struct Graph
{
    int nV, *visited;
    struct node **adjlist;
};
struct node *create(int v)
{
    struct node *new = (struct node *)malloc(sizeof(struct node));
    new->vertex = v;
    new->next = NULL;
    return new;
}
struct Graph *Graphinit(int nV)
{
    struct Graph *graph = (struct Graph *)malloc(sizeof(struct Graph));
    graph->nV = nV;
    graph->adjlist = malloc(nV * sizeof(struct node *));
    graph->visited = malloc(nV * sizeof(int));
    for (int i = 0; i < nV; i++)
    {
        graph->adjlist[i] = NULL;
        graph->visited[i] = 0;
    }
    return graph;
}
void addedge(struct Graph *graph, int src, int dest)
{
    //undirected so twice connection
    struct node *front = create(dest);
    front->next = graph->adjlist[src];
    graph->adjlist[src] = front;

    front = create(src);
    front->next = graph->adjlist[dest];
    graph->adjlist[dest] = front;
}
void adjlistprint(struct Graph *graph)
{
    for (int i = 0; i < graph->nV; i++)
    {
        struct node *t = graph->adjlist[i];
        printf("\n Vertex %d\n: ", i);
        while (t)
        {
            printf("%d->", t->vertex);
            t = t->next;
        }
        printf("\n");
    }
    printf("\n");
} /*
void main()
{
    struct Graph *graph = Graphinit(V);
    addedge(graph, 0, 1);
    addedge(graph, 0, 2);
    addedge(graph, 0, 3);
    addedge(graph, 1, 2);
    adjlistprint(graph);
}*/