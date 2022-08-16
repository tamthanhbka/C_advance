#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio_ext.h>
#include "lib/jrb.h"
#include "lib/dllist.h"

#define INFINITIVE_VALUE 100000
#define VALUE 200
typedef struct
{
    JRB edges;
    JRB vertices;
} * Graph;

void menu();
void case1(Graph graph);
void case2(Graph graph);
void case3(Graph graph);
void case5(Graph graph);
void case4(Graph graph);

Graph createGraph();         //Khoi tao
void dropGraph(Graph graph); // free
void addEdge(Graph graph, int v1, int v2);
void addVertex(Graph graph, int id, char *name); // them dinh moi
void Print_ver(Graph graph);
int indegree(Graph graph, int v, int *input);   // tra ve dinh cha
int outdegree(Graph graph, int v, int *output); // tra ve dinh con
void idlancan(char str[], int arr[]);
int dem(char str[]);
char *getVertex_name(Graph graph, int id); // lay ten dinh
void Print(JRB root);
int sosanh(int arr1[], int arr2[], int n1, int n2);
int hasEdge(Graph graph, int v1, int v2);

int main()
{
    int scan;
    char hoi;
    Graph g = createGraph();

    do
    {
        menu();
        scanf("%d", &scan);
        __fpurge(stdin);
        while (scan != 1 && scan != 2 && scan != 3 && scan != 4 && scan != 5 && scan != 6)
        {
            printf("Nhap sai!!!(chi duoc nhap cac so tu 1 den 6), moi nhap lai: ");
            scanf("%d", &scan);
            __fpurge(stdin);
        }
        switch (scan)
        {
        case 1:
            case1(g);
            printf("submitted at 5:51\n");
            break;
        case 2:
            case2(g);
            break;
        case 3:
            case3(g);
            break;
        case 4:
            case4(g);
            break;
        case 5:
            case5(g);
            break;
        case 6:
            printf("\n\t\t\tThank you\n\n");
            break;
        }
    } while (scan != 6);
    dropGraph(g);
    return 0;
}
void menu()
{
    printf("\n\n\n\n\t\t\t===========MeNu===================\n");
    printf("\t\t\t%4s1.Input Data \n", " ");
    printf("\t\t\t%4s2.List friend \n", " ");
    printf("\t\t\t%4s3.Popular person \n", " ");
    printf("\t\t\t%4s4.Check friend \n", " ");
    printf("\t\t\t%4s5.Suggest friend \n", " ");
    printf("\t\t\t%4s6.Exit \n", " ");
    printf("\t\t\t==================================\n");
    printf("...........Lua chon cua ban: ");
}
void case1(Graph graph)
{
    FILE *f1, *f2;
    int n, id, arr[100], m;
    char name[100], str[100];
    f1 = fopen("user.txt", "r");
    if (f1 == NULL)
    {
        printf("Loi doc file!\n");
    }
    f2 = fopen("friend.txt", "r");
    if (f2 == NULL)
    {
        printf("Loi doc file!\n");
    }
    printf("Data user\n");
    fscanf(f1, "%d", &n);
    printf("%d\n", n);
    for (int i = 0; i < n; i++)
    {
        fscanf(f1, "%d%s", &id, name);
        printf("%d %s\n", id, name);
        addVertex(graph, id, name);
    }
    printf("\n\nData friend\n");
    for (int i = 0; i < n; i++)
    {
        fgets(str, 100, f2);
        str[strlen(str) - 1] = '\0';
        printf("%s\n", str);
        m = dem(str);
        idlancan(str, arr);
        for (int j = 0; j < m; j++)
        {
            addEdge(graph, arr[0], arr[j + 1]);
        }
    }
}
void case2(Graph graph)
{
    JRB node, root;
    char name[100];
    int id = 0, out, output[100];
    printf("Nhap vao ho ten:");
    fgets(name, 100, stdin);
    name[strlen(name) - 1] = '\0';
    root = graph->vertices;
    jrb_traverse(node, root)
    {
        if (strcmp(name, jval_s(node->val)) == 0)
        {
            id = jval_i(node->key);
        }
    }
    if (id == 0)
    {
        printf("Nguoi dung khong co ban be\n");
    }
    printf("Danh sach ban be:\n");
    out = outdegree(graph, id, output);
    if (out == 0)
    {
        printf("Nguoi dung khong co ban be\n");
    }
    for (int i = 0; i < out; i++)
    {
        printf("%s\n", getVertex_name(graph, output[i]));
    }
}
void case3(Graph graph)
{
    JRB Rank, root, node;
    int u, odeg, out[1000];
    Rank = make_jrb();
    root = graph->vertices;
    jrb_traverse(node, root)
    {
        u = jval_i(node->key);
        odeg = outdegree(graph, u, out);
        jrb_insert_int(Rank, odeg, new_jval_i(u));
    }
    printf("%-37s%s\n", "Nguoi dung", "So ban be");
    jrb_rtraverse(node, Rank)
    {
        printf("%-40s%d\n", getVertex_name(graph, jval_i(node->val)), jval_i(node->key));
    }
}

void case4(Graph graph)
{
    JRB node, root;
    int id1, id2, check;
    char name1[100], name2[100];
    printf("Nhap vao ho ten nguoi thu nhat:");
    fgets(name1, 100, stdin);
    __fpurge(stdin);
    name1[strlen(name1) - 1] = '\0';
    root = graph->vertices;
    jrb_traverse(node, root)
    {
        if (strcmp(name1, jval_s(node->val)) == 0)
        {
            id1 = jval_i(node->key);
        }
    }
    printf("Nhap vao ho ten nguoi thu hai:");
    fgets(name2, 100, stdin);
    __fpurge(stdin);
    name2[strlen(name2) - 1] = '\0';
    root = graph->vertices;
    jrb_traverse(node, root)
    {
        if (strcmp(name2, jval_s(node->val)) == 0)
        {
            id2 = jval_i(node->key);
        }
    }
    check = hasEdge(graph, id1, id2);
    if (check)
    {
        printf("Hai nguoi la ban be\n");
    }
    else
    {
        printf("Hai nguoi khong la ban be\n");
    }
}
void case5(Graph graph)
{
    JRB node, root;
    char name[100];
    int out1[100], out2[100], o1, o2, id = -1, friend;
    printf("Nhap vao ho ten:");
    fgets(name, 100, stdin);
    name[strlen(name) - 1] = '\0';
    root = graph->vertices;
    jrb_traverse(node, root)
    {
        if (strcmp(name, jval_s(node->val)) == 0)
        {
            id = jval_i(node->key);
        }
    }
    printf("%d\n", id);
    o1 = outdegree(graph, id, out1);
    printf("%d\n", o1);
    for (int i = 0; i < o1; i++)
    {
        o2 = outdegree(graph, out1[i], out2);
        printf("%d\n", o2);
        friend = sosanh(out1, out2, o1, o2);
        printf("%d\n", friend);
        if (friend != -1)
        {
            printf("Goi y ket ban: %s\n", getVertex_name(graph, friend));
        }
        else
        {
            printf("Khong co goi y\n");
        }
    }
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
char *getVertex_name(Graph graph, int id) // lay ten dinh
{
    JRB node = jrb_find_int(graph->vertices, id);
    if (node == NULL)
        return NULL;
    else
        return jval_s(node->val);
}
void Print(JRB root)
{
    JRB node;
    jrb_traverse(node, root)
    {
        printf("tamtam\n");
        printf("Name : %s   ID : %d\n", jval_s(node->val), jval_i(node->key));
    }
}
int hasEdge(Graph graph, int v1, int v2)
{
    JRB node = jrb_find_int(graph->edges, v1);
    if (!node)
    {
        return 0;
    }
    else
    {
        JRB tree = jrb_find_int((JRB)jval_v(node->val), v2);
        if (!tree)
        {
            return 0;
        }
        return 1;
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
int sosanh(int arr1[], int arr2[], int n1, int n2)
{
    if (n1 < n2)
    {
        for (int i = 0; i < n1; i++)
        {
            for (int j = 0; j < n2; j++)
            {
                if (arr1[i] == arr2[j])
                    return arr1[i];
            }
        }
        return -1;
    }
    else
    {
        for (int i = 0; i < n2; i++)
        {
            for (int j = 0; j < n1; j++)
            {
                if (arr2[i] == arr1[j])
                    return arr2[i];
            }
        }
        return -1;
    }
}
