#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <climits>
#include <cmath>
#include <cstring>
#include <string>
#include <algorithm>
#include <iomanip>
#define SIZE 1001
using namespace std;

typedef struct Node {
    int weight;
    int speed;
    int origNum;
} mouse;

mouse arr[SIZE];
int dp[SIZE], pre[SIZE];

bool cmpRule(mouse a, mouse b)
{
    return a.weight < b.weight;
}

void printAns(int pos)
{
    if (pos == -1)
        return;
    printAns(pre[pos]);
    cout << arr[pos].origNum << endl;
}

int main()
{
    ios::sync_with_stdio(false);
    int cntPt = 0, weight, speed;
    while (cin >> weight >> speed)
    {
        arr[cntPt].weight = weight;
        arr[cntPt].speed = speed;
        arr[cntPt].origNum = cntPt + 1;
        cntPt++;
    }

    sort(arr, arr + cntPt, cmpRule);

    for (int i = 0; i < cntPt; i++)
    {
        dp[i] = 1;
        pre[i] = -1;
    }

    for (int i = 0; i < cntPt; i++)
    {
        for (int j = 0; j < i; j++)
        {
            if (arr[i].weight > arr[j].weight && arr[i].speed < arr[j].speed)
            {
                // dp[i] = max(dp[i], dp[j] + 1);
                if (dp[i] < dp[j] + 1)
                {
                    dp[i] = dp[j] + 1;
                    pre[i] = j;  // When solving ith sub-problem we introduced j.
                }
            }
        }
    }

    int ans = 0, pos = -1;
    for (int i = 0; i < cntPt; i++)
    {
        if (dp[i] > ans)
        {
            ans = dp[i];
            pos = i;  // Last node.
        }
    }

    cout << ans << endl;
    printAns(pos);  // Print answer reversely.
    return 0;
}
