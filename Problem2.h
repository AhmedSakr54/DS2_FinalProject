#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <queue>
#include <vector>
using namespace std;

typedef struct Cell
{
    int X,Y;
    Cell* parent;
}Cell;

Cell* newCell(int x, int y)
{
    Cell* newCell = (Cell*)malloc(sizeof(Cell));
    newCell->X = x;
    newCell->Y = y;
    return newCell;
}

int** initialize_maze(int N)
{
    int ** arr = (int**) malloc(N*sizeof(int*));
    for(int i =0; i<N; i++)
    {
        arr[i] = (int*) malloc(N*sizeof(int));
    }
    return arr;
}

bool checkIfLegalcell(Cell* currentCell, int**maze, bool isVisited, int a, int b)
{
    if (maze[currentCell->X+a][currentCell->Y+b] == 0)
    {
        if (!isVisited)
            return true;
    }
    return false;
}

void printPath(Cell* currentCell)
{
    vector<Cell*> path;

    while (currentCell->parent != NULL)
    {
        path.push_back(currentCell);
        currentCell = currentCell->parent;
    }
    path.push_back(currentCell);
    for (int i = path.size()-1; i > 0; i--)
    {
        printf("\(%d,%d\),",*(path[i]));
    }
    printf("\(%d,%d\)\n",*(path[0]));
}
void getPath(int** maze,int N)
{
    if (maze[0][0] == 1 || maze[N-1][N-1] == 1)
    {
        printf("No path found\n");
        return;
    }
    bool visited[N][N];
    queue<Cell*> q;
    Cell* currentCell = newCell(0,0);
    q.push(currentCell);
    visited[0][0] = true;
    while(!q.empty())
    {
        currentCell = q.front();
        q.pop();
        if (currentCell->Y-1 >= 0)
        {
            if (checkIfLegalcell(currentCell,maze,visited[currentCell->X][currentCell->Y-1],0,-1))
            {
                Cell* temp = newCell(currentCell->X, currentCell->Y-1);
                q.push(temp);
                temp->parent = currentCell;
                visited[temp->X][temp->Y] = true;
            }
        }
        if (currentCell->Y+1 < N)
        {
            if (checkIfLegalcell(currentCell,maze,visited[currentCell->X][currentCell->Y+1],0,1))
            {
                Cell* temp = newCell(currentCell->X, currentCell->Y+1);
                q.push(temp);
                temp->parent = currentCell;
                visited[temp->X][temp->Y] = true;
            }
        }
        if (currentCell->X-1 >= 0)
        {
            if (checkIfLegalcell(currentCell,maze,visited[currentCell->X-1][currentCell->Y],-1,0))
            {
                Cell* temp = newCell(currentCell->X-1, currentCell->Y);
                q.push(temp);
                temp->parent = currentCell;
                visited[temp->X][temp->Y] = true;
            }
        }
        if (currentCell->X+1 < N)
        {
            if (checkIfLegalcell(currentCell,maze,visited[currentCell->X+1][currentCell->Y],1,0))
            {
                Cell* temp = newCell(currentCell->X+1, currentCell->Y);
                q.push(temp);
                temp->parent = currentCell;
                visited[temp->X][temp->Y] = true;
            }
        }
        if (currentCell->X == N-1 && currentCell->Y == N-1)
            break;
    }
    if (!visited[N-1][N-1])
    {
        printf("No path found\n");
        return;
    }
    printPath(currentCell);
}


void Part2()
{
    int N;
    printf("please enter N:\n");
    scanf("%d", &N);
    printf("please enter values for maze:\n");
    int** maze = initialize_maze(N);
    for(int i=0; i<N; i++)
    {
        for(int j=0; j<N; j++)
            scanf("%d", &maze[i][j]);
    }
    printf("Solution:\n");
    getPath(maze,N);
}

