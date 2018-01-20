#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <string>
#include <iomanip>
#include <climits>
#include <vector>
#include <set>
#include <queue>
#define SIZE 100008
using namespace std;

bool check[SIZE];
int prime[SIZE];
int primePt = 0;

void init()
{
    primePt = 0;
    memset(check, false, sizeof(check));
    for (int i = 2; i < SIZE; i++)
    {
        if (!check[i])
        {
            prime[primePt++] = i;
        }
        for (int j = 0; j < primePt && i * prime[j] < SIZE; j++)
        {
            check[i * prime[j]] = true;
            if (i % prime[j] == 0)
            {
                break;
            }
        }
    }
}

int main()
{
    init();
    ios::sync_with_stdio(false);
    int verticeNum, edgeNum;
    cin >> verticeNum >> edgeNum;
    cout << 2 << " ";

    int pos = lower_bound(prime + 0, prime + primePt, verticeNum) - prime;  // verticeNum - 2 + 2
    cout << prime[pos] << endl;

    int cntEdgeNum = 0;
    cout << 1 << " " << verticeNum << " " << 2 << endl;
    cntEdgeNum++;

    for (int i = 1; i < verticeNum - 2 && cntEdgeNum < edgeNum; i++)
    {
        cout << i << " " << i + 1 << " " << 1 << endl;
        cntEdgeNum++;
    }

    if (cntEdgeNum < edgeNum)
    {
        cout << verticeNum - 2 << " " << verticeNum - 1 << " " << prime[pos] - verticeNum + 1 << endl; // prime[pos] - 2 - (verticeNum - 3)
        cntEdgeNum++;

        if (cntEdgeNum < edgeNum)
        {
            cout << verticeNum - 1 << " " << verticeNum << " " << prime[pos] + 1 << endl;
            cntEdgeNum++;
        }

        for (int i = 1; i <= verticeNum && cntEdgeNum < edgeNum; i++)
        {
            for (int j = i + 2; j <= verticeNum && cntEdgeNum < edgeNum; j++)
            {
                if (i == 1 && j == verticeNum)
                {
                    continue;
                }
                cout << i << " " << j << " " << prime[pos] + 1 << endl;
                cntEdgeNum++;
            }
        }
    }
    return 0;
}
