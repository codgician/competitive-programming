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

typedef struct _Edge
{
    int to;
    int next;
} Edge;

Edge arr[SIZE];
int head[SIZE], arrPt;
bool hasInDeg[SIZE];
int vertexNum;

int valArr[SIZE];
long long int dscArr[SIZE], dscPt;

int bitArr[SIZE];

long long int lim, ans;

int getLowbit(int n)
{
    return n & -n;
}

void add(int pos, int val)
{
    for (int i = pos; i <= vertexNum; i += getLowbit(i))
    {
        bitArr[i] += val;
    }
}

long long int getPrefixSum(int pos)
{
    long long int ans = 0;
    for (int i = pos; i > 0; i -= getLowbit(i))
    {
        ans += bitArr[i];
    }
    return ans;
}

void addEdge(int from, int to)
{
    arr[arrPt] = {to, head[from]};
    head[from] = arrPt++;
}

void dfs(int cntPt)
{
    ans += getPrefixSum(lower_bound(dscArr, dscArr + dscPt, (valArr[cntPt] == 0 ? LLONG_MAX : lim / valArr[cntPt])) - dscArr + 1);
    add(lower_bound(dscArr, dscArr + dscPt, valArr[cntPt]) - dscArr + 1, 1);
    for (int i = head[cntPt]; i != -1; i = arr[i].next)
    {
        int nextPt = arr[i].to;
        dfs(nextPt);
    }
    add(lower_bound(dscArr, dscArr + dscPt, valArr[cntPt]) - dscArr + 1, -1);
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
        memset(head, -1, sizeof(head));
        memset(hasInDeg, false, sizeof(hasInDeg));
        arrPt = 0;
        ans = 0;
        cin >> vertexNum >> lim;
        for (int i = 0; i < vertexNum; i++)
        {
            cin >> valArr[i];
            if (valArr[i] == 0)
                dscArr[i] = LLONG_MAX;
            else
                dscArr[i] = lim / valArr[i];
        }

        sort(dscArr + 0, dscArr + vertexNum);
        dscPt = unique(dscArr + 0, dscArr + vertexNum) - dscArr;

        for (int i = 0; i < vertexNum - 1; i++)
        {
            int from, to;
            cin >> from >> to;
            from--;
            to--;
            addEdge(from, to);
            hasInDeg[to] = true;
        }

        // Find root vertex
        for (int i = 0; i < vertexNum; i++)
        {
            if (!hasInDeg[i])
                dfs(i);
        }
        cout << ans << endl;
    }
    return 0;
}