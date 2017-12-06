#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <string>
#include <iomanip>
#include <climits>
#define SIZE 100001
using namespace std;

typedef struct _Edge {
    int startPt;
    int endPt;
} edge;

edge edgeArr[SIZE];

int arr[SIZE];
bool hasMentioned[SIZE];

int maxNode = 0;
bool hasLoop = false;

void init()
{
    maxNode = 0;
    hasLoop = false;
    memset(hasMentioned, false, sizeof(hasMentioned));
    for (int i = 0; i < SIZE; i++)
    {
        arr[i] = i;
    }
}

int getParent(int n)
{
    if (arr[n] == n)
        return n;
    else
    {
        arr[n] = getParent(arr[n]);
        return arr[n];
    }
}

void mergeNode(int a, int b)
{
    int aParent = getParent(a);
    int bParent = getParent(b);

    if (aParent != bParent)
        arr[bParent] = aParent;
    else
        hasLoop = true;
}

bool isValid()
{
    if (hasLoop)
        return false;

    int num = 0;
    for (int i = 0; i <= maxNode; i++)
    {
        if (hasMentioned[i] && arr[i] == i)
        {
            num++;
            if (num > 1)
                return false;
        }
    }
    return true;
}

int main()
{
    ios::sync_with_stdio(false);
    int a, b;
    init();
    while (cin >> a >> b)
    {
        if (a == -1 && b == -1)
            break;
        else if (a == 0 && b == 0)
        {
            if (isValid())
                cout << "Yes" << endl;
            else
                cout << "No" << endl;
            init();
        }
        else
        {
            maxNode = (maxNode, max(a, b));
            hasMentioned[a] = true;
            hasMentioned[b] = true;
            mergeNode(a, b);
        }
    }
    return 0;
}
