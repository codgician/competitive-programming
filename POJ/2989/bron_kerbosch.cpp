#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <string>
#include <cstring>
#include <iomanip>
#include <climits>
#include <vector>
#include <set>
#include <queue>
#include <map>
#define SIZE 128
using namespace std;

bool arr[SIZE][SIZE];
int all[SIZE][SIZE], some[SIZE][SIZE], none[SIZE][SIZE];

int ans;

void dfs(int depth, int allNum, int someNum, int noneNum)
{
    if (ans > 1000)
        return;

    if (someNum == 0 && noneNum == 0)
        ans++;

    int pivot = some[depth][0];
    for (int i = 0; i < someNum; i++)
    {
        int cntVertex = some[depth][i];
        if (arr[pivot][cntVertex])
            continue;

        for (int j = 0; j < allNum; j++)
        {
            all[depth + 1][j] = all[depth][j];
        }
        all[depth + 1][allNum] = cntVertex;

        int nxtSomeNum = 0, nxtNoneNum = 0;
        for (int j = 0; j < someNum; j++)
        {
            if (some[depth][j] != -1 && arr[cntVertex][some[depth][j]])
                some[depth + 1][nxtSomeNum++] = some[depth][j];
        }
        for (int j = 0; j < noneNum; j++)
        {
            if (arr[cntVertex][none[depth][j]])
                none[depth + 1][nxtNoneNum++] = none[depth][j];
        }

        dfs(depth + 1, allNum + 1, nxtSomeNum, nxtNoneNum);

        some[depth][i] = -1;
        none[depth][noneNum++] = cntVertex;
    }

}

int main()
{
    ios::sync_with_stdio(false);
    int nodeNum, edgeNum;
    while (cin >> nodeNum >> edgeNum)
    {
        memset(arr, false, sizeof(arr));
        ans = 0;

        for (int i = 0; i < edgeNum; i++)
        {
            int from, to;
            cin >> from >> to;
            from--;
            to--;
            arr[from][to] = true;
            arr[to][from] = true;
        }

        for (int i = 0; i < nodeNum; i++)
            some[0][i] = i;
        dfs(0, 0, nodeNum, 0);

        if (ans > 1000)
            cout << "Too many maximal sets of friends." << endl;
        else
            cout << ans << endl;
    }
    return 0;
}
