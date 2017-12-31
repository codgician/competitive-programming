#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <string>
#include <iomanip>
#include <climits>
#define SIZE 999
using namespace std;

bool isTrap[SIZE];
int dx[3] = {1, 2, 3};
int blockNum, trapNum, life, ans;

bool canMove(int cntx)
{
    if (cntx > blockNum)
        return false;
    return true;
}

void dfs(int cntx, int trapCount)
{
    if (trapCount >= life)
        return;

    if (cntx == blockNum)
    {
        ans++;
        return;
    }

    for (int i = 0; i < 3; i++)
    {
        int nextx = cntx + dx[i];
        if (canMove(nextx))
        {
            if (isTrap[nextx])
                dfs(nextx, trapCount + 1);
            else
                dfs(nextx, trapCount);
        }

    }

}

int main()
{
    ios::sync_with_stdio(false);
    cin >> blockNum >> trapNum >> life;
    memset(isTrap, false, sizeof(isTrap));
    for (int i = 0; i < trapNum; i++)
    {
        int tmp;
        cin >> tmp;
        isTrap[tmp] = true;
    }
    ans = 0;
    dfs(0, 0);
    cout << ans << endl;
    return 0;
}
