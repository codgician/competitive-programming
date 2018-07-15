#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <string>
#include <cstring>
#include <iomanip>
#include <climits>
#include <stack>
#include <queue>
#include <vector>
#include <set>
#include <map>
#include <functional>
#include <iterator>
using namespace std;

#define DEPTH_SIZE 30
#define SIZE 100100

int arr[DEPTH_SIZE][SIZE];
int tmp[SIZE], ans[SIZE];
int tmpLen, ansLen;

void dfs(int depth, int cntLen)
{
    if (depth > 20)
        return;

    if (cntLen == 1 && arr[depth][0] == 0)
    {
        if (ansLen == 0 || ansLen > tmpLen)
        {
            ansLen = tmpLen;
            for (int i = 0; i < tmpLen; i++)
            {
                ans[i] = tmp[i];
            }
        }
        return;
    }

    bool hasOdd = false;
    for (int i = 0; i < cntLen; i++)
    {
        if (arr[depth][i] & 1)
        {
            hasOdd = true;
            break;
        }
    }

    if (hasOdd)
    {
        int nextLen;

        // Try 1
        tmp[tmpLen++] = 1 << depth;
        for (int i = 0; i < cntLen; i++)
            arr[depth + 1][i] = (arr[depth][i] & 1) ? (arr[depth][i] - 1) >> 1 : arr[depth][i] >> 1;
        nextLen = unique(arr[depth + 1] + 0, arr[depth + 1] + cntLen) - arr[depth + 1];
        dfs(depth + 1, nextLen);
        tmpLen--;

        // Try -1
        tmp[tmpLen++] = -(1 << depth);
        for (int i = 0; i < cntLen; i++)
            arr[depth + 1][i] = (arr[depth][i] & 1) ? (arr[depth][i] + 1) >> 1 : arr[depth][i] >> 1;
        nextLen = unique(arr[depth + 1] + 0, arr[depth + 1] + cntLen) - arr[depth + 1];
        dfs(depth + 1, nextLen);
        tmpLen--;

    }
    else
    {
        for (int i = 0; i < cntLen; i++)
            arr[depth + 1][i] = arr[depth][i] >> 1;
        dfs(depth + 1, cntLen);
    }
}

int main()
{
    ios::sync_with_stdio(false);
    int num;
    cin >> num;
    for (int i = 0; i < num; i++)
    {
        cin >> arr[0][i];
    }

    sort(arr[0] + 0, arr[0] + num);
    int cntLen = unique(arr[0] + 0, arr[0] + num) - arr[0];

    tmpLen = 0;
    ansLen = 0;
    dfs(0, cntLen);

    cout << ansLen << endl;
    for (int i = 0; i < ansLen; i++)
    {
        cout << ans[i];
        if (i < ansLen - 1)
            cout << " ";
        else
            cout << endl;
    }

    return 0;
}