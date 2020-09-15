#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <queue>

using namespace std;
class Graph
{
    public:
    int numVertices;
    int **adjMatrix;
    Graph(int V)
    {
        numVertices = V;
        adjMatrix = (int**) malloc(V*sizeof(int*));
        for(int i =0; i<V; i++)
        {
            adjMatrix[i] = (int*) malloc(V*sizeof(int));
        }
        for(int i=0; i<V; i++)
            for(int j=0; j<V; j++)
                adjMatrix[i][j] = 0;
    }
    void addEdge(int u, int v)
    {
        adjMatrix[u-1][v-1] = 1;
        adjMatrix[v-1][u-1] = 1;
    }
    int get_connected_people(int start, int k)
    {
        int number = 0;
        queue<int> q;
        int s = start-1;
        bool visited[numVertices];
        int n[numVertices];
        int level = 0;
        for (int i=0; i<numVertices; i++)
        {
            visited[i] = false;
            n[i] = 0;
        }
        q.push(s);
        visited[s] = true;
        while (!q.empty())
        {
            s = q.front();
            q.pop();
            for (int i = 0; i<numVertices; i++)
            {
                if (adjMatrix[s][i] > 0 && !visited[i])
                {
                    q.push(i);
                    visited[i] = true;
                    if (level+1 < numVertices)
                        n[level+1]++;
                    if (level+1 == k)
                        number++;
                    if (level+1 > k)
                        break;
                }
            }
            n[level]--;
            if (n[level] <= 0)
                level++;
        }
        return number;
    }
};

void Part1()
{
    int V,E,start,k;
    printf("please enter number of vertices:\n");
    scanf("%d" , &V);
    printf("please enter number of edges:\n");
    scanf("%d" , &E);
    Graph g(V);
    printf("please enter edges in the form (u v):\n");
    for(int i=0; i<E; i++)
    {
        int u,v;
        scanf("%d %d" ,&u,&v);
        g.addEdge(u,v);
    }

    printf("please enter starting vertex:\n");
    scanf("%d" , &start);
    printf("please enter value k:\n");
    scanf("%d" , &k);
    int num_connected_people = g.get_connected_people(start,k);
    printf("There are %d people with %d connections away starting from %d\n" , num_connected_people, k, start);
}


