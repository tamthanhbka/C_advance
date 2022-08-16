// Do thi co huong
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jrb.h"
#include "dllist.h"
typedef struct graph
{
    JRB edges;
    JRB vertices;
} Graph;

Graph createGraph();                             //Khoi tao graph
void addVertex(Graph graph, int id, char *name); //Them dinh
char *getVertex(Graph graph, int id);            //Lay ra en dinh
void addEdge(Graph graph, int v1, int v2);       //Them mot canh tu v1->v2
int hasEdge(Graph graph, int v1, int v2);        //v1->v2?
int indegree(Graph graph, int v, int *output);
int outdegree(Graph graph, int v, int *output);
int DAG(Graph graph);
void dropGraph(Graph graph);
int main()
{
    Graph g = createGraph();
    addVertex(g, 0, "V0");
    addVertex(g, 1, "V1");
    addVertex(g, 2, "V2");
    addVertex(g, 3, "V3");
    addEdge(g, 0, 1);
    addEdge(g, 1, 2);
    addEdge(g, 2, 0);
    addEdge(g, 1, 3);
    if (DAG(g))
        printf("The graph is acycle\n");
    else
        printf("Have cycles in the graph\n");
    return 0;
}
Graph createGraph()
{
    Graph G;
    // G = ( Graph*)malloc(sizeof(Graph));
    G.edges = make_jrb();
    G.vertices = make_jrb();
    return G;
}
void addVertex(Graph graph, int id, char *name)
{
    if (jrb_find_int(graph.vertices, id) == NULL)
    {
        jrb_insert_int(graph.vertices, id, new_jval_s(name));
    }
    else
        return;
}
char *getVertex(Graph graph, int id)
{

    if (jrb_find_int(graph.vertices, id) == NULL)
    {
        return NULL;
    }
    else
    {
        return jval_s(graph.vertices->val);
    }
}

void addEdge(Graph graph, int v1, int v2)
{
    JRB node;
    node = jrb_find_int(graph.edges, v1);
    JRB tree;
    if (node == NULL)
    {
        tree = make_jrb();
        jrb_insert_int(graph.edges, v1, new_jval_v(tree));
        jrb_insert_int(tree, v2, new_jval_i(1));
    }
    else
    {
        tree = (JRB)jval_v(node->val);
        jrb_insert_int(tree, v2, new_jval_i(1));
    }
}

int hasEdge(Graph graph, int v1, int v2)
{
    JRB node;
    node = jrb_find_int(graph.edges, v1);
    if (node == NULL)
    {
        return 0;
    }
    else
    {
        if(jrb_find_int(node,v2)==NULL)
        {
            return 0;
        }
        else{
            return 1;
        }
    }
}
int indegree(Graph graph, int v, int *output)
{
    JRB node,tree;
  node=NULL;
  int key;
  int total;
  total=0;
  jrb_traverse(node,graph.vertices)
    {
      key = jval_i(node->key);
      if(hasEdge(graph,key,v)==1&&key!=v)
    output[total++]=key;
    }
  return total;
}
int outdegree(Graph graph, int v, int *output)
{
     JRB node,tree;
  int total;
  node=jrb_find_int(graph.edges,v);
  if(node==NULL)
    return 0;
  else
    {
      tree=(JRB) jval_v(node->val);
      total=0;
      jrb_traverse(node,tree)
    output[total++]=jval_i(node->key);
      return total;
    }
}
int getAdjacentVertices(JRB graph,int v,int *output)
{
  JRB node,tree;
  int total;
  node=jrb_find_int(graph,v);
  if(node==NULL)
    return 0;
  else
    {
      tree=(JRB) jval_v(node->val);
      total=0;
      jrb_traverse(node,tree)
    output[total++]=jval_i(node->key);
      return total;
    }
}
int DAG(Graph graph)
{
     int visited[1000] = {};
  int start;
   int n, output[100], i, u, v;
   Dllist node, stack;
    JRB node2;
  jrb_traverse(node2, graph.vertices)
    {
      start=jval_i(node2->key);
   stack = new_dllist();
   dll_append(stack, new_jval_i(start));

 

   while ( !dll_empty(stack) )
   {
      node = dll_last(stack);
      u = jval_i(node->val);
      dll_delete_node(node);
      if (!visited[u]) 
      {
          visited[u] = 1;
          if ( u == start ) return 0;           
          n = getAdjacentVertices(graph.edges, u, output);
          for (i=0; i<n; i++)
          {
              v = output[i];
              if (!visited[v])
                 dll_append(stack, new_jval_i(v));
          }
      }
   }
    }
   return 1;
}
void dropGraph(Graph graph)
{
    JRB node;
    jrb_traverse(node, graph.vertices)
        jrb_free_tree(jval_v(node->val));
    jrb_traverse(node, graph.edges)
        jrb_free_tree(jval_v(node->val));
}