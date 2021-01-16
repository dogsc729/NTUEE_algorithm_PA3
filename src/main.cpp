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

using namespace std;
struct Edge
{
    int start_v;
    int end_v;
    int weight;
};

void help_message()
{
    cout << "usage: ./cb <input file name> <output file name>" << endl;
}
void ugraph_cyc_detection(fstream &, fstream &)
{
}
void dgraph_cyc_detection(fstream &, fstream &)
{
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
    for (int i = 0; i < num_of_edges; i++)
    {
        int start_v;
        int end_v;
        int weight;
        fin >> start_v >> end_v >> weight;
    }
    fin.close();
    fout.close();
    return 0;
}