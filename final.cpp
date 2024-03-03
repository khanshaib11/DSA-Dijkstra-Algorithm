#include <iostream>
#include <limits.h>

using namespace std;

#define V 10

int minKey(int key[], bool mstSet[])
{
    int min = INT_MAX, min_index;

    for (int v = 0; v < V; v++)
        if (mstSet[v] == false && key[v] < min)
            min = key[v], 
            min_index = v;

    return min_index;
}

void printPath(int parent[], int j, string cities[])
{
    if (parent[j] == -1)
        return;

    printPath(parent, parent[j], cities);
    cout << " -> " << cities[j];
}

void printPathAndDistance(int dist[], int parent[], int n, string cities[], int s)
{
    cout << "Vertex\t\tDistance from Source\t\tPath\n";
    for (int i = 0; i < n; i++)
    {
        cout << cities[i] << "\t\t" << dist[i] << "KM\t\t\t";
        cout << cities[s];
        printPath(parent, i, cities);
        cout << endl;
    }
}

void printGraphData(const string cities[], const int graph[V][V])
{
    cout << "Cities: ";
    for (int i = 0; i < V; i++)
    {
        cout << cities[i];
        if (i != V - 1)
        {
            cout << ",";
        }
    }
    cout << endl;

    cout << "Graph:\n";
    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            cout << graph[i][j];
            if (j != V - 1)
            {
                cout << ",";
            }
        }
        cout << endl;
    }
}

void dij(int graph[V][V], string cities[], int source)
{
    int distance[V];
    int parent[V];
    bool bools1[V];
    int n = V;

    for (int i = 0; i < n; i++)
    {
        distance[i] = INT_MAX;
        parent[i] = -1;
        bools1[i] = false;
    }

    distance[source] = 0;

    for (int co = 0; co < n - 1; co++)
    {
        int index = minKey(distance, bools1);
        bools1[index] = true;

        for (int j = 0; j < n; j++)
        {
            if (bools1[j] == false && graph[index][j] != 0 && distance[j] > graph[index][j] + distance[index])
            {
                distance[j] = graph[index][j] + distance[index];
                parent[j] = index;
            }
        }
    }

    printPathAndDistance(distance, parent, n, cities, source);
}

int main()
{
    string cities[V] = {"Rawalpindi", "Islamabad", "Peshawar", "Mardan", "Dera-Ismael-Khan", "Dera-Ghazi-Khan", "Karachi", "Faizabad", "Jamal-Wanda", "Golra-Mor"};

    int graph[V][V] = {
        {0, 30, 0, 0, 0, 0, 0, 8, 0, 10},
        {30, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 4, 0, 0, 2, 0},
        {0, 0, 0, 0, 0, 14, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 10, 0, 0, 0, 0},
        {0, 0, 4, 14, 10, 0, 2, 0, 0, 0},
        {0, 0, 0, 0, 0, 2, 0, 1, 6, 0},
        {8, 0, 0, 0, 0, 0, 1, 0, 7, 0},
        {0, 0, 2, 0, 0, 0, 6, 7, 0, 0},
        {10, 0, 0, 0, 0, 0, 0, 0, 0, 0}};

    printGraphData(cities, graph);

    dij(graph, cities, 1);
    cout << endl;

    return 0;
}