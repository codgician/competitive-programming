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

int in[SIZE];
bool hasMentioned[SIZE];

int maxPt = 0;
bool notTree = false;

void init()
{
    notTree = false;
    maxPt = 0;
    for (int i = 0; i < SIZE; i++)
    {
        in[i] = 0;
        hasMentioned[i] = false;
    }
}

bool isTree()
{
    int inZeroNum = 0;

    if (notTree)
        return false;

    for (int i = 0; i <= maxPt; i++)
    {
        if (!hasMentioned[i])
            continue;
        if (in[i] == 0)
            inZeroNum++;
        if (inZeroNum > 1)
            return false;
        if (in[i] > 1)
            return false;
    }
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
            in[b]++;
            maxPt = max(maxPt, max(a, b));
            if (a == b)
                notTree = true;
        }
    }
    return 0;
}
