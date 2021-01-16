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
    vector<bool> visited(num_of_vertices, false);
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
        for (int i = 0; i < num_of_edges; i++)
        {
            int start_v;
            int end_v;
            int weight;
            fin >> start_v >> end_v >> weight;
            edges.push_back({start_v, end_v, weight});
        }
    }
    fin.close();
    fout.close();
    return 0;
}