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
void help_message()
{
    cout << "usage: ./cb <input file name> <output file name>" << endl;
}
void ugraph_cyc_detection()
{
}
void dgraph_cyc_detection()
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
    getline(fin, identifier);
    if (identifier == "u")
        ugraph_cyc_detection();
    else
        dgraph_cyc_detection();
    fin.close();
    fout.close();
    return 0;
}