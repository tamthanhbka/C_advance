//set graph du dung cay do den 
#include <stdio.h>
#include <stdio_ext.h>
#include <stdlib.h>
#include "jrb.h"
#include "jval.h"
typedef JRB Graph;
Graph createGraph()
{
    Graph g = make_jrb();
    return g;
}
void addEdge(Graph graph, int v1, int v2)
{
    Graph node;
    node = jrb_find_int(graph, v1);
    Graph tree;
    if (node == NULL)
    {
        tree = make_jrb();
        jrb_insert_int(graph, v1, new_jval_v(tree));
        jrb_insert_int(tree, v2, new_jval_i(1));
    }
    else
    {
        tree = (JRB)jval_v(node->val);
        jrb_insert_int(tree, v2, new_jval_i(1));
    }
    node = jrb_find_int(graph, v2);
    if (node == NULL)
    {
        tree = make_jrb();
        jrb_insert_int(graph, v2, new_jval_v(tree));
        jrb_insert_int(tree, v1, new_jval_i(1));
    }
    else
    {
        tree = (JRB)jval_v(node->val);
        jrb_insert_int(tree, v1, new_jval_i(1));
    }
}
int getAdjacentVertices(Graph graph, int v, int *output)
{
    Graph node;
    node = jrb_find_int(graph, v);
    int total = 0;
    if (node == NULL)
    {
        printf("Khong ton tai nut\n");
    }
    else
    {
        Graph tree;
        tree = (JRB)jval_v(node->val);

        jrb_traverse(node, tree)
            output[total++] = jval_i(node->key);
    }
    return total;

} //lấy các đỉnh kề của 1 đỉnh cho trước
void dropGraph(Graph graph)
{
    Graph node;
    jrb_traverse(node, graph)
        jrb_free_tree(jval_v(node->val));
}
int main()
{
    Graph g;
    int n, output[100];
    g = createGraph();
    addEdge(g, 0, 1);
    addEdge(g, 0, 2);
    addEdge(g, 1, 2);
    addEdge(g, 1, 3);
    n = getAdjacentVertices(g, 1, output);
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