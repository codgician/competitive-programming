#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <string>
#include <iomanip>
#include <climits>
#include <set>
#include <vector>
#include <queue>
#define SIZE 1001
using namespace std;

int parent[SIZE];
bool isLeaf[SIZE];
int childrenNum[SIZE];

int main()
{
    ios::sync_with_stdio(false);
    int num;
    cin >> num;
    memset(childrenNum, 0, sizeof(childrenNum));
    memset(isLeaf, true, sizeof(isLeaf));
    parent[0] = 0;
    isLeaf[0] = false;
    for (int i = 1; i < num; i++)
    {
        cin >> parent[i];
        parent[i]--;
        isLeaf[parent[i]] = false;
    }

    for (int i = 0; i < num; i++)
    {
        if (isLeaf[i])
        {
            childrenNum[parent[i]]++;
        }
    }

    int minChildrenNum = SIZE;
    for (int i = 0; i < num; i++)
    {
        if (!isLeaf[i])
        {
            minChildrenNum = min(minChildrenNum, childrenNum[i]);
        }
    }
    if (minChildrenNum < 3)
        cout << "No" << endl;
    else
        cout << "Yes" << endl;
    return 0;
}
