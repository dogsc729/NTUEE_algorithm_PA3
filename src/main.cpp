// **************************************************************************
//  File       [main.cpp]
//  Author     [Shu-Yu Lin]
//  Synopsis   [The main program of 2020 fall Algorithm PA3]
// **************************************************************************

#include <cstring>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <bits/stdc++.h>
#include <new>
#include <ctime>
#include <map>
#include <algorithm>
#include <queue>

using namespace std;
struct Edge
{
    int start_v;
    int end_v;
    int weight;
};

bool compare(const Edge &edge1, const Edge &edge2)
{
    return edge1.weight > edge2.weight;
}
int findroot(vector<int> root, int x)
{
    int a = x;
    while (x != root[x])
    {
        x = root[x];
    }
    int z;
    while (a != root[a])
    {
        z = a;
        a = root[a];
        root[z] = x;
    }
    return x;
}

bool cycle_detect_BFS(int s, int n, vector<vector<int>> adj_list)
{
    bool colored[n]; //number of vertices,colored or not
    for (int i = 0; i < n; i++)
        colored[i] = false; //initialize
    queue<int> Q;
    colored[s] = true;
    Q.push(s);
    while (!Q.empty())
    {
        int u = Q.front();
        Q.pop();
        for (int i = 0; i < adj_list[u].size(); i++)
        {
            if (colored[adj_list[u][i]])
            {
                return true;
            }
            else
            {
                colored[adj_list[u][i]] = true;
                Q.push(adj_list[u][i]);
            }
        }
    }
    return false;
}

void kruskal_u(vector<Edge> &arr, int m, fstream &fout)
{
    int n = arr.size();
    int removed_weight = 0;
    vector<Edge> removed_edges;
    cout << m << " " << n << endl;
    sort(arr.begin(), arr.end(), compare);
    vector<int> root(m);
    for (int i = 0; i < m; i++)
    {
        root[i] = i;
    }
    int rootstart;
    int rootend;
    for (int i = 0; i < n; i++)
    {
        rootstart = findroot(root, arr[i].start_v);
        rootend = findroot(root, arr[i].end_v);
        if (rootstart != rootend)
        {
            root[rootstart] = rootend;
        }
        else
        {
            removed_edges.push_back({arr[i].start_v, arr[i].end_v, arr[i].weight});
            removed_weight = removed_weight + arr[i].weight;
        }
    }
    fout << removed_weight << endl;
    for (int i = 0; i < removed_edges.size(); i++)
    {
        fout << removed_edges[i].start_v << " " << removed_edges[i].end_v << " " << removed_edges[i].weight << endl;
    }
}
void kruskal_d(vector<Edge> &arr, int m, fstream &fout)
{
    int n = arr.size();
    vector<Edge> removed_edges;
    vector<Edge> remained_edges;
    vector<Edge> test_edges;
    cout << m << " " << n << endl;
    sort(arr.begin(), arr.end(), compare);
    vector<int> root(m);
    for (int i = 0; i < m; i++)
    {
        root[i] = i;
    }
    int rootstart;
    int rootend;
    for (int i = 0; i < n; i++)
    {
        rootstart = findroot(root, arr[i].start_v);
        rootend = findroot(root, arr[i].end_v);
        if (rootstart != rootend)
        {
            root[rootstart] = rootend;
            remained_edges.push_back({arr[i].start_v, arr[i].end_v, arr[i].weight});
        }
        else
        {
            removed_edges.push_back({arr[i].start_v, arr[i].end_v, arr[i].weight});
        }
    }
    sort(removed_edges.begin(), removed_edges.end(), compare);
    vector<vector<int>> adj_list(m);
    //make a adjacency list for remaining edges
    for (int i = 0; i < remained_edges.size(); i++)
    {
        adj_list[remained_edges[i].start_v].push_back(remained_edges[i].end_v);
        //cout << remained_edges[i].start_v << " " << remained_edges[i].end_v << endl;
    }
    /*for (int i = 0; i < adj_list.size(); i++)
    {
        cout << i << endl;
        for (int j = 0; j < adj_list[i].size(); j++)
        {
            cout << adj_list[i][j] << " ";
        }
        cout << endl;
    }*/
    //check whether each removed edges can be inserted into the graph
    for (int i = 0; i < removed_edges.size(); i++)
    {
        //add adjacency list
        adj_list[removed_edges[i].start_v].push_back(removed_edges[i].end_v);
        //cout << removed_edges[i].start_v << endl;
        //add the removed edge into the remaining edges
        remained_edges.push_back(removed_edges[i]);
        //check if cycle exist
        if (cycle_detect_BFS(removed_edges[i].start_v, m, adj_list) == true)
        //remove testing edges
        {
            //cout << "fuck" << endl;
            //捨棄那個edge
            remained_edges.pop_back();
            //移除adjlist
            adj_list[removed_edges[i].start_v].pop_back();
        }
        //keep testing edges
        else
        {
            removed_edges[i].start_v = 0;
            removed_edges[i].end_v = 0;
            removed_edges[i].weight = 0;
            //cout << "hello" << endl;
        }
    }
    int removed_weight = 0;
    for (int i = 0; i < removed_edges.size(); i++)
    {
        if (removed_edges[i].start_v != 0 && removed_edges[i].end_v != 0 && removed_edges[i].weight != 0)
        {
            removed_weight = removed_weight + removed_edges[i].weight;
        }
    }
    fout << removed_weight << endl;
    for (int i = 0; i < removed_edges.size(); i++)
    {
        if (removed_edges[i].start_v != 0 && removed_edges[i].end_v != 0 && removed_edges[i].weight != 0)
        {
            fout << removed_edges[i].start_v << " " << removed_edges[i].end_v << " " << removed_edges[i].weight << endl;
        }
    }
    for (int i = 0; i < remained_edges.size(); i++)
    {
        cout << remained_edges[i].start_v << " " << remained_edges[i].end_v << endl;
    }
}

void help_message()
{
    cout << "usage: ./cb <input file name> <output file name>" << endl;
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        help_message();
        return 0;
    }
    fstream fin(argv[1]);
    fstream fout;
    fout.open(argv[2], ios::out);
    string identifier;
    int num_of_vertices;
    int num_of_edges;
    fin >> identifier >> num_of_vertices >> num_of_edges;
    vector<Edge> edges;
    if (identifier == "u")
    {
        for (int i = 0; i < num_of_edges; i++)
        {
            int start_v;
            int end_v;
            int weight;
            fin >> start_v >> end_v >> weight;
            edges.push_back({start_v, end_v, weight});
        }
        kruskal_u(edges, num_of_vertices, fout);
    }
    if (identifier == "d")
    {
        vector<Edge> removed_edges;
        for (int i = 0; i < num_of_edges; i++)
        {
            int start_v;
            int end_v;
            int weight;
            fin >> start_v >> end_v >> weight;
            edges.push_back({start_v, end_v, weight});
        }
        kruskal_d(edges, num_of_vertices, fout);
    }
    fin.close();
    fout.close();
    return 0;
}