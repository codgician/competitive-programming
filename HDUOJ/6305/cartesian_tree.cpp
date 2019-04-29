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

#define SIZE 1000010

const long long int mod = 1e9 + 7;

typedef struct _TreeNode
{
    int parent;
    int leftSon, rightSon;
    int value;
    int size;
} TreeNode;

TreeNode treeArr[SIZE];

long long int invArr[SIZE];

long long int fastPow(long long int a, long long int n)
{
    long long int ans = 1;
    a %= mod;
    while (n > 0)
    {
        if (n & 1)
            ans = ans * a % mod;
        a = a * a % mod;
        n >>= 1;
    }
    return ans;
}

void initInv()
{
    invArr[1] = 1;
    for (int i = 2; i < SIZE; i++)
        invArr[i] = (mod - mod / i) * invArr[mod % i] % mod;
}

int build(int len)
{
    stack<int> stk;
    for(int i = 0; i < len; ++i)
    {
        int lastPop = -1;
        while (!stk.empty() && treeArr[stk.top()].value < treeArr[i].value)
        {
            lastPop = stk.top();
            stk.pop();
        }

        if (!stk.empty())
        {
            treeArr[i].parent = stk.top();
            treeArr[stk.top()].rightSon = i;
        }

        if (lastPop != -1)
        {
            treeArr[lastPop].parent = i;
            treeArr[i].leftSon = lastPop;
        }

        stk.push(i);
    }

    int rootPt = -1;
    while (!stk.empty())
    {
        rootPt = stk.top();
        stk.pop();
    }

    return rootPt;
}

void dfs(int cntPt)
{
    if (cntPt == -1)
        return;
    treeArr[cntPt].size = 1;
    dfs(treeArr[cntPt].leftSon);
    dfs(treeArr[cntPt].rightSon);
    treeArr[cntPt].size += treeArr[treeArr[cntPt].leftSon].size + treeArr[treeArr[cntPt].rightSon].size;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    initInv();
    int caseNum;
    cin >> caseNum;
    while (caseNum--)
    {
        int len;
        cin >> len;
        for (int i = 0; i < len; i++)
        {
            cin >> treeArr[i].value;
            treeArr[i].parent = -1;
            treeArr[i].leftSon = -1;
            treeArr[i].rightSon = -1;
        }

        int rootPt = build(len);
        dfs(rootPt);

        long long int ans = len * invArr[2] % mod;
        for (int i = 0; i < len; i++)
        {
            ans *= invArr[treeArr[i].size];
            ans %= mod;
        }
        cout << ans << endl;
    }
    return 0;
}