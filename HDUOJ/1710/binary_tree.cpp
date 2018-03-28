#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <string>
#include <iomanip>
#include <climits>
#include <vector>
#include <queue>
#include <map>
#include <set>
#define SIZE 1001
using namespace std;

int preOrder[SIZE], inOrder[SIZE], postOrder[SIZE];
int ansPt;

void preIn2Post(int prePt, int inPt, int len)
{
    if (len <= 0)
    {
        return;
    }
    if (len == 1)
    {
        postOrder[ansPt++] = preOrder[prePt];
        return;
    }


    int i = 0;
    while (preOrder[prePt] != inOrder[inPt + i])
    {
        i++;
    }
    preIn2Post(prePt + 1, inPt, i);
    preIn2Post(prePt + i + 1, inPt + i + 1, len - i - 1);

    postOrder[ansPt++] = preOrder[prePt];
}

int main()
{
    ios::sync_with_stdio(false);
    int n;
    while (cin >> n)
    {
        for (int i = 0; i < n; i++)
            cin >> preOrder[i];
        for (int i = 0; i < n; i++)
            cin >> inOrder[i];

        ansPt = 0;
        preIn2Post(0, 0, n);

        for (int i = 0; i < n; i++)
        {
            cout << postOrder[i];
            if (i < n - 1)
                cout << " ";
            else
                cout << endl;
        }
    }
    return 0;
}
