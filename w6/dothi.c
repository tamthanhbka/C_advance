#include <stdio.h>
#include <stdio_ext.h>
#include <stdlib.h>
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
void dropGraph(Graph graph)
{
    free(graph.matrix);
}
int main()
{
    int i, n, output[100];

    Graph G;
    G = createGraph(100);
    // printf("a\n");
    addEdge(G, 0, 1);
    addEdge(G, 0, 2);
    addEdge(G, 1, 2);
    addEdge(G, 1, 3);
    //  printf("a\n");
    n = getAdjacentVertices(G, 1, output);
    printf("%d\n", n);
    if (n == 0)
    {
        printf("Khong co dinh ke cua nut 1\n");
    }
    else
    {
        printf("Cac dinh ke cua 1 la:\n");
        for (int i = 0; i < n; i++)
        {
            printf("%3d", output[i]);
        }
        printf("\n");
    }
    return 0;
}
