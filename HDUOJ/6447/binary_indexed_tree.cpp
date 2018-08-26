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

#define SIZE 100010

typedef struct _Node
{
    int x, y;
    int val;
} Node;

Node arr[SIZE];
int yArr[SIZE];
int dp[SIZE];
int bitArr[SIZE];
int vertexNum, ans;

int getLowbit(int n)
{
    return n & -n;
}

void update(int pos, int val)
{
    for (int i = pos; i <= vertexNum; i += getLowbit(i))
    {
        bitArr[i] = max(bitArr[i], val);
    }
}

int getPrefixMax(int pos)
{
    int ans = 0;
    for (int i = pos; i > 0; i -= getLowbit(i))
    {
        ans = max(ans, bitArr[i]);
    }
    return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int caseNum;
    cin >> caseNum;
    while (caseNum--)
    {
        memset(bitArr, 0, sizeof(bitArr));
        cin >> vertexNum;

        bool hasOrig = false;
        for (int i = 0; i < vertexNum; i++)
        {
            cin >> arr[i].x >> arr[i].y >> arr[i].val;
            yArr[i] = arr[i].y;
            if (arr[i].x == 0 && arr[i].y == 0)
                hasOrig = true;
        }

        if (!hasOrig)
        {
            arr[vertexNum].x = 0;
            arr[vertexNum].y = 0;
            arr[vertexNum].val = 0;
            yArr[vertexNum] = 0;
            vertexNum++;
        }

        sort(yArr + 0, yArr + vertexNum);
        sort(arr + 0, arr + vertexNum, [](Node & fst, Node & snd) {
            if (fst.x == snd.x)
                return fst.y > snd.y;
            return fst.x < snd.x;
        });

        for (int i = 0; i < vertexNum; i++)
        {
            arr[i].y = lower_bound(yArr + 0, yArr + vertexNum, arr[i].y) - yArr + 1;
            dp[i] = arr[i].val;
        }

        for (int i = 0; i < vertexNum; i++)
        {
            dp[i] = max(dp[i], getPrefixMax(arr[i].y - 1) + arr[i].val);
            update(arr[i].y, dp[i]);
        }

        int ans = 0;
        for (int i = 0; i < vertexNum; i++)
        {
            ans = max(ans, dp[i]);
        }

        cout << ans << endl;
    }

    return 0;
}