#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <string>
#include <iomanip>
#include <climits>
#include <vector>
#include <queue>
#include <set>
#include <map>
#define SIZE 26
using namespace std;

int parent[SIZE];

void init()
{
    for (int i = 0; i < SIZE; i++)
    {
        parent[i] = i;
    }
}

int getParent(int i)
{
    int rootNode = i;
    while (rootNode != parent[rootNode])
        rootNode = parent[rootNode];
    int cntNode = rootNode;
    while (cntNode != rootNode)
    {
        int tmp = parent[cntNode];
        parent[cntNode] = rootNode;
        cntNode = tmp;
    }
    return rootNode;
}

void mergeNode(int a, int b)
{
    int aParent = getParent(a);
    int bParent = getParent(b);

    if (bParent != 'b' - 'a' && aParent != bParent)
    {
        parent[bParent] = aParent;
    }
}

int main()
{
    ios::sync_with_stdio(false);
    init();
    string str;
    while (cin >> str)
    {
        if (str == "0")
        {
            if (getParent('m' - 'a') == 'b' - 'a')
                cout << "Yes." << endl;
            else
                cout << "No." << endl;
            init();
        }
        else
        {
            mergeNode(str[0] - 'a', str[str.length() - 1] - 'a');
        }
    }
    return 0;
}
