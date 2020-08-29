#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>

using namespace std;

class Graph
{
private:
    vector<vector<bool>> adj;
    size_t vertNum;

    bool isEdge(int v, int path[], int pos)
    {
        if (adj[path[pos - 1]][v] == 0)
            return false;
        for (int i = 0; i < pos; i++)
            if (path[i] == v)
                return false;
        return true;
    }

    bool hamCycle(int path[], int pos)
    {
        if (pos == vertNum)
        {
            if (adj[path[pos - 1]][path[0]] == 1)
                return true;
            else
                return false;
        }

        for (int v = 1; v < vertNum; v++)
        {
            if (isEdge(v, path, pos))
            {
                path[pos] = v;
                if (hamCycle(path, pos + 1) == true)
                    return true;
                /*path[pos] = -1;*/
            }
        }
        return false;
    }

    void printSolution(int path[])
    {
        cout << "Solution:" << endl;
        for (int i = 0; i < vertNum; i++)
            cout << path[i] << "  ";
        cout << path[0] << endl;
    }
public:

    bool hamCycle()
    {
        int* cycle = new int[vertNum];
        /*for (int i = 0; i < vertNum; i++)
            path[i] = -1;*/
        cycle[0] = 0;
        if (hamCycle(cycle, 1) == false)
        {
            cout << "\nSolution does not exist\n\n";
            return false;
        }
        printSolution(cycle);
        delete[] cycle;
        return true;
    }

    Graph(vector<vector<bool>> adj)
    {
        this->adj = adj;
        vertNum = adj.size();
    }

    /*   Graph(int vertNum)
   {
       adj.reserve(vertNum);
       for (size_t i = 0; i < vertNum; i++)
       {
           adj[i].reserve(vertNum);
       }
   }*/

    //void addEdge(int u, int v)
    //{
    //    if (u == v)
    //        adj[u][v] = 1;
    //    else
    //    {
    //        adj[u][v] = 1;
    //        adj[v][u] = 1;
    //    }
    //}

    //void remEdge(int u, int v)
    //{
    //    if (u == v)
    //        adj[u][v] = 0;
    //    else
    //    {
    //        adj[u][v] = 1;
    //        adj[v][u] = 0;
    //    }
    //}

};

int main()
{
    Graph g1(     
        {
            {0, 1, 0, 1, 0},
            {1, 0, 1, 1, 1},
            {0, 1, 0, 0, 1},
            {1, 1, 0, 0, 1},
            {0, 1, 1, 1, 0}
        });
    /*
       (0)--(1)--(2)
        |   / \   |
        |  /   \  |
        | /     \ |
       (3)-------(4)
    */
    g1.hamCycle();
    Graph g2(
        {
            {0, 1, 0, 0, 1},
            {1, 0, 1, 0, 0},
            {0, 1, 0, 1, 0},
            {0, 0, 1, 0, 0},
            {1, 0, 0, 0, 0}
        });
    /*
       (0)--(1)--(2)
        |   / \   |
        |  /   \  |
        | /     \ |
       (4)       (3)
    */
    g2.hamCycle();
    Graph g3(
        {
            {0, 1, 0, 1, 0, 0, 0 ,0 ,1},
            {1, 0, 1, 0, 0, 0, 0 ,0 ,1},
            {0, 1, 0, 0, 0, 0, 0 ,1 ,1},
            {1, 0, 0, 0, 1, 1, 0 ,0 ,0},
            {0, 0, 0, 1, 0, 1, 0 ,0 ,0},
            {0, 0, 0, 1, 1, 0, 1 ,1 ,0},
            {0, 0, 0, 0, 0, 1, 0 ,1 ,0},
            {0, 0, 1, 0, 0, 1, 1 ,0 ,0},
            {1, 1, 1, 0, 0, 0, 0 ,0 ,0}
        });
    /*
    (0)--(1)--(2)
     | \  |  / |
    (3)  (8)  (7)
     | \     / |
    (4)--(5)--(6)
    */
    g3.hamCycle();

    return 0;
}