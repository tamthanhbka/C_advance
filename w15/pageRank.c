
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio_ext.h>
#include "lib/jrb.h"
#include "lib/dllist.h"
#define VALUE 200
typedef struct
{
    JRB edges;
    JRB vertices;
} * Graph;

Graph createGraph();                             //Khoi tao
void dropGraph(Graph graph);                     // free
void addVertex(Graph graph, int id, char *name); // them dinh moi
void addEdge(Graph graph, int v1, int v2);       // them canh
void Print_ver(Graph graph);                     // in do thi ra man hinh
int indegree(Graph graph, int v, int *input);    // tra ve dinh cha
int outdegree(Graph graph, int v, int *output);  // tra ve dinh con
void sosanh(Graph graph, int arrID[], int n);
void pageRank(Graph graph, JRB Rank, int solanlap);
int BFS(Graph graph, int start, int stop, int *rank); //

int dem(char str[]);
void idlancan(char str[], int arr[]);

int main()
{
    char str[VALUE], name[VALUE], id[5];
    int N, n, m, arr[7], arrID[6], input[VALUE], nip, length[VALUE];
    JRB RankPage, node, tree, node1;
    RankPage = make_jrb();
    FILE *f1, *f2;
    f1 = fopen("webpages.txt", "r");
    if (f1 == NULL)
    {
        printf("Loi doc file!\n");
    }

    f2 = fopen("pageConnect.txt", "r");
    if (f2 == NULL)
    {
        printf("Loi doc file!\n");
    }

    Graph g = createGraph();
    //doc file thu nhat va them dinh
    fgets(str, VALUE, f1);
    str[strlen(str) - 1] = '\0';
    N = atoi(str);
    for (int i = 0; i < n; i++)
    {
        fscanf(f1, "%s", name);
        fscanf(f1, "%s", id);
        addVertex(g, atoi(id), name);
    }
    //printf("%d\n", n);
    //doc file thu hai va them canh
    fgets(str, VALUE, f2);
    str[strlen(str) - 1] = '\0';
    n = atoi(str);
    for (int i = 0; i < n; i++)
    {
        fgets(str, VALUE, f2);
        str[strlen(str) - 1] = '\0';
        m = dem(str);
        idlancan(str, arr);
        for (int j = 0; j < m; j++)
        {
            addEdge(g, arr[0], arr[j + 1]);
        }
    }
    nip = indegree(g, 2011, input);
    for (int i = 0; i < nip; i++)
    {
        printf("%8d", input[i]);
    }
    printf("\n");
    sosanh(g, arrID, N);
    for (int j = 0; j < N; j++)
    {
        printf("%8d", arrID[j]);
    }
    printf("\nMAX : %d\n", arrID[0]);
    printf("MIN : %d\n", arrID[5]);
    pageRank(g, RankPage, 3);
    printf("tam\n");
    jrb_traverse(node, RankPage)
    {
        printf("ID: %d -- Rankpage : %f\n", jval_i(node->val), jval_d(node->key));
    }
    //Print_ver(g);
    printf("\n\n");
    printf("Khoang cach : %d\n", BFS(g, 1015, 1012, length));
    dropGraph(g);
    return 0;
}

Graph createGraph() //Khoi tao
{
    Graph g;
    g = (Graph)malloc(sizeof(Graph));
    g->edges = make_jrb();
    g->vertices = make_jrb();
    return g;
}
void dropGraph(Graph graph) // free
{
    JRB node, root;
    root = graph->edges;
    jrb_traverse(node, root)
    {
        jrb_free_tree((JRB)jval_v(node->val));
    }
    jrb_free_tree(root);
    root = graph->vertices;
    jrb_traverse(node, root)
    {
        free(jval_s(node->val));
    }
    jrb_free_tree(graph->vertices);
}

void addVertex(Graph graph, int id, char *name) // them dinh moi
{
    JRB node = jrb_find_int(graph->vertices, id);
    if (node == NULL)
    { // only add new vertex
        JRB node1 = make_jrb();
        jrb_insert_int(graph->edges, id, new_jval_v(node1));
        jrb_insert_int(graph->vertices, id, new_jval_s(strdup(name)));
    }
}

void addEdge(Graph graph, int v1, int v2)
{
    JRB node, tree, node1;
    node = jrb_find_int(graph->edges, v1);
    if (node == NULL)
    {
        return;
    }
    tree = (JRB)jval_v(node->val);
    node1 = jrb_find_int(tree, v2);
    if (node1 == NULL)
    {
        jrb_insert_int(tree, v2, new_jval_i(1));
    }
}
void Print_ver(Graph graph)
{
    JRB node;
    jrb_traverse(node, graph->vertices)
    {
        printf("ID : %d Name : %s\n", jval_i(node->key), jval_s((node->val)));
    }
}
int indegree(Graph graph, int v, int *input) // tra ve dinh cha
{
    JRB tree, node;
    int total = 0;
    jrb_traverse(node, graph->edges)
    {
        tree = (JRB)jval_v(node->val);
        if (jrb_find_int(tree, v))
        {
            input[total] = jval_i(node->key);
            total++;
        }
    }
    return total;
}

int outdegree(Graph graph, int v, int *output) // tra ve dinh con
{
    JRB tree, node;
    int total;
    node = jrb_find_int(graph->edges, v);
    if (node == NULL)
        return 0;
    tree = (JRB)jval_v(node->val);
    total = 0;
    jrb_traverse(node, tree)
    {
        output[total] = jval_i(node->key);
        total++;
    }
    return total;
}
void sosanh(Graph graph, int arrID[], int n)
{
    JRB node, root;
    int i = 0, input[VALUE], tmp;
    root = graph->vertices;
    jrb_traverse(node, root)
    {
        arrID[i] = jval_i(node->key);
        i++;
    }
    for (int i = 0; i < n; i++)
    {
        if (indegree(graph, arrID[i], input) < indegree(graph, arrID[i + 1], input))
        {
            tmp = arrID[i];
            arrID[i] = arrID[i + 1];
            arrID[i + 1] = tmp;
        }
    }
}
void pageRank(Graph graph, JRB Rank, int solanlap)
{
    JRB node, root;
    root = graph->vertices;
    int inID, input[VALUE], id, output[VALUE], rpout;
    double rank;
    while (solanlap != 0)
    {
        jrb_traverse(node, root)
        {
            id = jval_i(node->key);
            rank = 0;
            inID = indegree(graph, id, input);
            for (int i = 0; i < inID; i++)
            {
                rpout = outdegree(graph, input[i], output);
                rank += (1 / (double)rpout);
            }
            jrb_insert_dbl(Rank, rank, new_jval_i(id));
        }
        solanlap--;
    }
}
// int BFS(Graph graph, int start, int stop)
// {
//     int *visited = malloc(sizeof(int) * 10000);
//     memset(visited, 0, sizeof(int) * 10000);
//     int n, output[10000], i, u, v, length = 0;
//     Dllist node, queue;
//     if (jrb_find_int(graph->vertices, start) == NULL || jrb_find_int(graph->vertices, stop) == NULL)
//     {
//         return -1;
//     }

//     queue = new_dllist();
//     dll_append(queue, new_jval_i(start));
//     //printf("Toi bi dien\n");

//     while (!dll_empty(queue))
//     {
//         node = dll_first(queue);
//         u = jval_i(node->val);
//         dll_delete_node(node);

//         if (!visited[u])
//         {
//             visited[u] = 1;
//             if (u == stop)
//             {
//                 free(visited);
//                 return length;
//             }
//             n = outdegree(graph, u, output);
//             for (i = 0; i < n; i++)
//             {
//                 v = output[i];
//                 length++;
//                 if (!visited[v])
//                     dll_append(queue, new_jval_i(v));
//             }
//         }
//     }
//     free(visited);
//     return -1;
// }
int BFS(Graph graph, int start, int stop, int *rank) //
{
    int visited[VALUE] = {};
    int n, output[100], u, v;
    Dllist node, queue;
    if (jrb_find_int(graph->vertices, start) == NULL || jrb_find_int(graph->vertices, stop) == NULL)
    {
        return -1;
    }
    queue = new_dllist();
    dll_append(queue, new_jval_i(start));
    for (int i = 0; i < VALUE; i++)
    {
        rank[i] = VALUE;
    }
    rank[start] = 0;
    while (!dll_empty(queue))
    {
        node = dll_first(queue);
        u = jval_i(node->val);
        dll_delete_node(node);
        if (!visited[u])
        {
            visited[u] = 1;
            if (rank[u] > rank[stop])
            {
                return rank[stop];
            }
            if (u == stop)
            {
                if (rank[u] < rank[stop])
                {
                    return rank[u];
                }
                return rank[stop];
            }
            n = outdegree(graph, u, output);
            for (int i = 0; i < n; i++)
            {
                v = output[i];
                if (rank[v] - 1 > rank[u])
                    rank[v] = rank[u] + 1;
                if (!visited[v])
                    dll_append(queue, new_jval_i(v));
            }
        }
    }
    return -1;
}

void ngatXau(char str[], char name[], char id[])
{
    int co = 0, dem = 0;
    for (int i = 0; i < strlen(str); i++)
    {
        if (str[i] == ' ')
        {
            co = 1;
        }
        if (co == 0)
        {
            name[i] = str[i];
            dem++;
        }
        if (co == 1)
        {
            id[i - dem] = str[i];
        }
    }
    for (int i = 0; i < strlen(id); i++)
    {
        id[i] = id[i + 1];
    }
}
int dem(char str[])
{
    int dem = 0;
    for (int i = 0; i < strlen(str); i++)
    {
        if (str[i] == ' ')
        {
            dem++;
        }
    }
    return dem;
}
void idlancan(char str[], int arr[])
{
    char *token;
    token = strtok(str, " ");
    int i = 0;
    while (token != NULL)
    {
        arr[i] = atoi(token);
        i++;
        token = strtok(NULL, " ");
    }
}
int DAG(Graph graph)
{
    int *visited = malloc(sizeof(int) * 10000);
    int n, output[100], i, u, v, start;
    Dllist node, stack;
    JRB vertex;

    jrb_traverse(vertex, graph->vertices)
    {
        memset(visited, 0, sizeof(int) * 10000);

        start = jval_i(vertex->key);
        stack = new_dllist();
        dll_append(stack, new_jval_i(start));

        while (!dll_empty(stack))
        {
            node = dll_last(stack);
            u = jval_i(node->val);
            dll_delete_node(node);
            if (!visited[u])
            {
                visited[u] = 1;
                n = outdegree(graph, u, output);
                for (i = 0; i < n; i++)
                {
                    v = output[i];
                    if (v == start)
                    { // cycle detected
                        free(visited);
                        return u;
                    }
                    if (!visited[v])
                        dll_append(stack, new_jval_i(v));
                }
            }
        }
    }
    free(visited);
    return -1; // no cycle
}
