#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <queue>
#define MAX 1e6

using namespace std;

typedef struct Edge
{
    int source,destination;
    int time,cost;
}Edge;
Edge* newEdge(int src, int dest, int t, int c)
{
    Edge * E = (Edge*) malloc(sizeof(Edge));
    E->source = src;
    E->cost = c;
    E->time = t;
    E->destination = dest;
    return E;
}
typedef struct COMP
{
    bool operator()(const pair<pair<int,int>,int>& a, const pair<pair<int,int>,int>& b)
    {
        if (a.first.first == b.first.first)
            return a.first.second > b.first.second;
        return  a.first.first>b.first.first;
    }
}COMP;

void addEdge(vector<Edge*> adjList[],int src,int dst,int time,int cost)
{
        Edge* e1 = newEdge(src-1,dst-1,time,cost);
        adjList[src-1].push_back(e1);
        Edge* e2 = newEdge(dst-1,src-1,time,cost);
        adjList[dst-1].push_back(e2);
}


void print_results(int k,int totalCost, int totalTime, int* parent)
{
    if (totalCost == MAX)
    {
        printf("there is no path between the source and the destination...");
        return;
    }
    vector<int> route;

    while (parent[k] >= 0)
    {
        route.push_back(k+1);
        k = parent[k];
    }
    route.push_back(k+1);
    printf("The route with minimum cost is ");
    for(int i = route.size()-1; i > 0; i--)
        printf("%d-->", route[i]);
    printf("%d\n", route[0]);
    printf("Total time %d hours\n", totalTime);
    printf("Total cost = %d$\n", totalCost);
}

void get_min_cost_route(int src, int dst, vector<Edge*> adjList[], int V, int M)
{
    priority_queue<pair< pair<int,int> ,int>, vector< pair< pair<int,int> ,int> >, COMP> pq;
    int d[V];  // cost
    int t[V]; // time
    int parent[V];
    src--;
    dst--;
    for (int i = 0; i < V; i++)
    {
        d[i] = MAX;
        t[i] = MAX;
    }
    d[src] = 0;
    t[src] = 0;
    parent[src] = -1;
    pq.push(make_pair(make_pair(d[src],t[src]),src));
    while (!pq.empty())
    {
        pair< pair<int,int>,int> pmin = pq.top();
        int u = pmin.second;
        //printf("u = %d d[u] = %d t[u] = %d\n" , u+1, d[u] , t[u]);
        pq.pop();
        for (int j = 0; j < adjList[u].size(); j++)
        {
            Edge* e = adjList[u][j];
            int i = e->destination;
            int possible_min_cost = d[u] + e->cost + (M*e->time);
            int possible_min_time = t[u] + e->time;
            if (possible_min_cost < d[i] || (possible_min_cost == d[i] && possible_min_time < t[i]))
            {
                d[i] = possible_min_cost;
                t[i] = t[u] + e->time;
                if (i != dst)
                {
                    d[i] += M;
                    t[i]++;
                }
                pq.push(make_pair(make_pair(d[i],t[i]),i));
                //printf("i = %d d[i] = %d t[i] = %d\n" , i+1, d[i] , t[i]);
                parent[i] = u;
            }
        }
    }
    print_results(dst,d[dst],t[dst],parent);
}

void Part3()
{
    int M,cities,routes;
    int src,dst,cost,time;
    printf("please enter amount M:\n");
    scanf("%d" , &M);
    printf("please enter number of cities:\n");
    scanf("%d", &cities);
    printf("please enter number of routes:\n");
    scanf("%d" , &routes);
    vector<Edge*> adjList[cities];
    printf("please enter source, destination, time and cost for each route:\n");
    for (int i=0; i < routes; i++)
    {
        scanf("%d %d %d %d" ,&src,&dst,&time,&cost);
        addEdge(adjList,src,dst,time,cost);
    }
    printf("please enter source city:\n");
    scanf("%d" , &src);
    printf("please enter destination city:\n");
    scanf("%d" , &dst);
    get_min_cost_route(src,dst,adjList,cities,M);
}


