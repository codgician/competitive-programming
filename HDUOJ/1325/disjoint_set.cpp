#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <string>
#include <iomanip>
#include <climits>
#define SIZE 1000010
using namespace std;

int arr[SIZE], in[SIZE];
bool hasMentioned[SIZE];

int maxPt = 0;
bool hasLoop = false;

void init()
{
    maxPt = 0;
    hasLoop = false;
    for (int i = 0; i < SIZE; i++)
    {
        arr[i] = i;
        hasMentioned[i] = false;
    }
}

int getParent(int n)
{
    if (arr[n] == n)
    {
        return n;
    }
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
    // b should only appear once! In degree should always be 1!
    if (b != bParent || aParent == bParent)
        hasLoop = true;
}

bool isTree()
{
    if (hasLoop)
        return false;

    int ans = 0;
    for (int i = 0; i <= maxPt; i++)
    {
        if (!hasMentioned[i])
            continue;
        if (arr[i] == i)
            ans++;
        // Should have only one root.
        if (ans > 1)
            return false;
    }

    return true;
}

int main()
{
    ios::sync_with_stdio(false);
    init();
    int a, b, caseNum = 1;
    while (cin >> a >> b)
    {
        if (a < 0 || b < 0)
            break;
        else if (a == 0 && b == 0)
        {
            if (isTree())
                cout << "Case " << caseNum << " is a tree." << endl;
            else
                cout << "Case " << caseNum << " is not a tree." << endl;
            caseNum++;
            init();
        }
        else
        {
            hasMentioned[a] = true;
            hasMentioned[b] = true;
            mergeNode(a, b);
            maxPt = max(maxPt, max(a, b));
        }
    }
    return 0;
}
