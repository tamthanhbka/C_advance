//Duyet graph theo chieu rong
#include <stdio.h>
#include <stdio_ext.h>
#include <stdlib.h>
#include "queue.h"
typedef struct
{
    int *matrix;
    int sizemax;
} Graph;
Graph createGraph(int sizemax)
{
    Graph dothi;
    dothi.sizemax = sizemax;
    dothi.matrix = (int *)malloc((sizemax * sizemax) * sizeof(int));
    for (int i = 0; i < sizemax; i++)
    {
        for (int j = 0; j < sizemax; j++)
        {
            dothi.matrix[i * sizemax + j] = 0;
        }
    }
    return dothi;
}
void addEdge(Graph graph, int v1, int v2)
{
    graph.matrix[v1 * graph.sizemax + v2] = 1;
    graph.matrix[v2 * graph.sizemax + v1] = 1;
}
int adjacent(Graph graph, int v1, int v2)
{
    if (graph.matrix[v1 * graph.sizemax + v2] == 0)
    {
        return 0;
    }
    return 1;
}
int getAdjacentVertices(Graph graph, int vertex, int *output)
{
    //output = (int *)malloc(graph.sizemax * sizeof(int));
    int j = 0;
    for (int i = 0; i < graph.sizemax; i++)
    {
        if (graph.matrix[vertex * graph.sizemax + i] == 1)
        {
            output[j] = i;
            j++;
        }
    }
    return j;
}
//ham duyet theo chieu rong
void BFS(Graph G, ElementType v)
{
    int visited[100];
    for (int i = 0; i < G.sizemax; i++)
    {
        visited[i] = 0;
    }
    ElementType x;
    //ElementType output[100];
    QUEUE *Q;
    Q = MakeNullQueue();
    EnQueue(Q, v);
    visited[v.val] = 1;

    while (!isEmptyQ(Q))
    {
        x = DeQueue(Q);
        if (visited[x.val] == 1)
        {
            //int n=getAdjacentVertices(G,x,output);
            for (int i = 0; i < G.sizemax; i++)
            {
                if (adjacent(G, x.val, i) == 1)
                {
                    if (visited[i] == 0)
                    {
                        ElementType tm;
                        tm.val = i;
                        EnQueue(Q, tm);
                        visited[tm.val] = 1;
                    }
                }
            }
            visited[x.val] = 2;
            printf("%5d", x);
        }
    }
}
void dropGraph(Graph graph)
{
    free(graph.matrix);
}
int main()
{
    //int i, n, output[100];
    int n;
    Graph G;
    G = createGraph(100);
    // printf("a\n");
    addEdge(G, 0, 1);
    addEdge(G, 0, 2);
    addEdge(G, 1, 2);
    addEdge(G, 1, 3);
    addEdge(G, 2, 3);
    addEdge(G, 2, 4);
    addEdge(G, 4, 5);
    //  printf("a\n");
    // n = getAdjacentVertices(G, 1, output);
    // printf("%d\n", n);
    // if (n == 0)
    // {
    //     printf("Khong co dinh ke cua nut 1\n");
    // }
    // else
    // {
    //     printf("Cac dinh ke cua 1 la:\n");
    //     for (int i = 0; i < n; i++)
    //     {
    //         printf("%3d", output[i]);
    //     }
    //     printf("\n");
    // }
    ElementType test;
    test.val = 1;
    BFS(G, test);
    // printf("tamtam\n");
    printf("\n");
    return 0;
}
