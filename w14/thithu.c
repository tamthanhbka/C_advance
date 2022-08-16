#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdio_ext.h>
#include "lib/jrb.h"
#include "lib/dllist.h"
#define INFINITIVE_VALUE  100

typedef struct {
   JRB edges;
   JRB vertices;
} Graph;

Graph createGraph();
void addVertex(Graph graph, char *name);
//char *getVertex(Graph graph, int id);// tra ve ten dinh
int getVertex_id(Graph graph, char* name);// tra ve id dinh 
void addEdge(Graph graph, char* v1, char* v2, int weight); // them canh noi v1 va v2
int getEdgeValue(Graph graph, char* v1, char* v2);
int indegree(Graph graph, int v, int* output);
int outdegree(Graph graph, int v, int* output);
void dropGraph(Graph graph);
int main()
{
    FILE *f;
    f = fopen("data.txt", "r");
    if(f == NULL)
    {
        printf("Loi doc file!\n");
    }
   
    Graph g = createGraph();
    char strline[INFINITIVE_VALUE], ten[5];
    int i, time, n;
    i = 0;
    fscanf(f,"%s",ten);
    addVertex(g,ten);
    while(!feof(f))
    {
       
    }
    return 0;
}




Graph createGraph()
{
   Graph g; 
   g.edges = make_jrb();  
   g.vertices = make_jrb();  
   return g;
}

void addVertex(Graph graph, char *name)
{
    JRB node = jrb_find_str(graph.vertices, name);
    if (node==NULL){ // only add new vertex  
        jrb_insert_str(graph.vertices,name,new_jval_i(1));
    }           
}

int getVertex_id(Graph graph, char * name)
{
    JRB node = jrb_find_str(graph.vertices, name);
    if (node==NULL)
        return 0;
    else 
        return jval_i(node->key);

}
// char *getVertex_name(Graph graph, int id)
// {
//      JRB node = jrb_find_int(graph.vertices, id);
//      if (node==NULL) 
//         return NULL;
//      else                
//         return jval_s(node->val);
// }     

void addEdge(Graph graph, char* v1, char* v2, int weight)
{
     JRB node, tree;
        node = jrb_find_str(graph.edges, v1);
        if (node==NULL) {
           tree = make_jrb();
           jrb_insert_str(graph.edges, v1, new_jval_v(tree));
        } else
        {
           tree = (JRB) jval_v(node->val); 
           
        }
        jrb_insert_str(tree, v2, new_jval_i(weight));
}

int getEdgeValue(Graph graph, char* v1, char* v2)
{
    JRB node, tree;
    node = jrb_find_str(graph.edges, v1);
    if (node==NULL){
       return INFINITIVE_VALUE;
    }else{
        tree = (JRB) jval_v(node->val);
        node = jrb_find_str(tree, v2);
        if (node==NULL)
            return INFINITIVE_VALUE;
        else
            return jval_i(node->val); 
    }      
}

// int indegree (Graph graph, char* v, char** output)
// {
//     JRB tree, node;
//     int total = 0;   
//     jrb_traverse(node, graph.edges)
//     {
//        tree = (JRB) jval_v(node->val);
//        if (jrb_find_int(tree, v))
//        {
//           output[total] = jval_i(node->key);
//           total++;
//        }                
//     }
//     return total;   
// }

// int outdegree (Graph graph, int v, int* output)
// {
//     JRB tree, node;
//     int total;
//     node = jrb_find_int(graph.edges, v);
//     if (node==NULL)
//        return 0;
//     tree = (JRB) jval_v(node->val);
//     total = 0;   
//     jrb_traverse(node, tree)
//     {
//        output[total] = jval_i(node->key);
//        total++;                
//     }
//     return total;   
// }
void dropGraph(Graph graph)
{
    JRB node, tree;
    jrb_traverse(node, graph.edges)
    {
        tree = (JRB) jval_v(node->val);
        jrb_free_tree(tree);
    }
    jrb_free_tree(graph.edges);
    jrb_free_tree(graph.vertices);
}
int idlancan(char str[], char *arr[])
{
    char *token;
    int dem=0;
    for(int i=0;i<strlen(str);i++)
    {
        if(str[i]=='-')
        dem++;
    }
    token = strtok(str, " :-");
    int i = 0;
    while (token != NULL)
    {
        arr[i] = token;
        i++;
        token = strtok(NULL, " :-");
    }
    
    return dem;
}
