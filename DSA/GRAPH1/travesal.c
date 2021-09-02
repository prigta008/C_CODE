#include "adjlist.c"
#define v 8
//q struct start
typedef struct Queue
{
    int top, rear, key[v];
} Q;
void InitializeQueue(Q *ptr)
{
    ptr->top = -1;
    ptr->rear = -1;
}
int SizeOfQueue(Q *ptr)
{
    if (((ptr->top) == 0) && ((ptr->rear) == 0))
        return 1;
    else if (ptr->top == -1)
        return 0;
    else
        return ((ptr->rear) - (ptr->top) + 1);
}
int IsFull(Q *ptr)
{
    if (SizeOfQueue(ptr) == v)
        return 1;
    else
        return 0;
}
int IsEmpty(Q *ptr)
{
    if (SizeOfQueue(ptr) == 0)
        return 1;
    else
        return 0;
}
void EnQueue(Q *ptr, int num)
{
    if (IsFull(ptr))
        printf("\nQueue is Full\n");
    else
    {
        if (IsEmpty(ptr))
        {
            ptr->top = 0;
            ptr->rear = 0;
        }
        else
            ptr->rear++;
        ptr->key[ptr->rear] = num;
    }
}
void DeQueue(Q *ptr)
{
    if (IsEmpty(ptr))
        printf("\nQueue is Empty...\n");
    if (SizeOfQueue(ptr) == 1)
    {
        ptr->rear = -1;
        ptr->top = -1;
    }
    else
        ptr->top++;
}

void dfs(struct Graph *graph, int start)
{
    struct node *adjlist = graph->adjlist[start];
    struct node *adj = adjlist;
    graph->visited[start] = 1;
    printf("%d ", start);
    while (adj != NULL)
    {
        int cn = adj->vertex;
        if (graph->visited[cn] == 0)
            dfs(graph, cn);
        adj = adj->next;
    }
}
void bfs(struct Graph *graph, int start, Q *q)
{//not working 
    graph->visited[start] = 1;
    EnQueue(q, start);
    while (!IsEmpty(q))
    {
        printf("%d ", q->key[q->top]);
        DeQueue(q);
        struct node *t = graph->adjlist[q->key[q->top]];
        while (t)
        {
            int d = t->vertex;
            if (graph->visited[d] == 0)
            {
                graph->visited[d] = 1;
                EnQueue(q, d);
            }
            t = t->next;
        }
    }
}

void main()
{
    struct Graph *graph = Graphinit(v);

    Q *q = malloc(sizeof(Q));
    InitializeQueue(q);

    addedge(graph, 0, 3);
    addedge(graph, 0, 4);
    addedge(graph, 2, 4);
    addedge(graph, 2, 1);
    addedge(graph, 5, 1);
    addedge(graph, 1, 6);
    addedge(graph, 5, 6);
    addedge(graph, 5, 7);
    addedge(graph, 6, 7);
    printf("\nDFS :\n ");
    dfs(graph, 0);
    printf("\n BFS :\n ");
    bfs(graph, 0, q);
}