#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <string>
#include <cstring>
#include <iomanip>
#include <climits>
#include <vector>
#include <queue>
#include <set>
#include <map>
#define leftSon (segPt << 1)
#define rightSon (segPt << 1 | 1)
#define SIZE 50010
using namespace std;

typedef struct _Employee
{
    int id;
    int ability;
    int loyalty;
} Employee;

Employee empArr[SIZE];

typedef struct _Edge
{
    int to;
    int next;
} Edge;

Edge arr[SIZE];
int head[SIZE], arrPt;

typedef struct _SegTree
{
    int leftPt, rightPt;
    int maxLoyalty;
} SegTree;

SegTree segTree[SIZE << 2];

map<int, int> mp;
int inTime[SIZE], outTime[SIZE], cntTime;
int ansArr[SIZE];

bool cmpRule(Employee &a, Employee &b)
{
    if (a.ability == b.ability)
        return a.id < b.id;
    return a.ability > b.ability;
}

void addEdge(int from, int to)
{
    arr[arrPt] = {to, head[from]};
    head[from] = arrPt++;
}

void dfs(int cntPt)
{
    inTime[cntPt] = cntTime++;

    int edgePt = head[cntPt];
    while (edgePt != -1)
    {
        int nextPt = arr[edgePt].to;
        dfs(nextPt);
        edgePt = arr[edgePt].next;
    }

    outTime[cntPt] = cntTime;
}

void pushUp(int segPt)
{
    segTree[segPt].maxLoyalty = max(segTree[leftSon].maxLoyalty, segTree[rightSon].maxLoyalty);
}

void build(int segPt, int leftPt, int rightPt)
{
    segTree[segPt].leftPt = leftPt;
    segTree[segPt].rightPt = rightPt;

    if (segTree[segPt].leftPt == segTree[segPt].rightPt)
    {
        segTree[segPt].maxLoyalty = -1;
        return;
    }

    int midPt = (leftPt + rightPt) >> 1;
    build(leftSon, leftPt, midPt);
    build(rightSon, midPt + 1, rightPt);
    pushUp(segPt);
}

void update(int segPt, int cntPt, int val)
{
    if (segTree[segPt].leftPt == segTree[segPt].rightPt)
    {
        segTree[segPt].maxLoyalty = val;
        return;
    }

    int midPt = (segTree[segPt].leftPt + segTree[segPt].rightPt) >> 1;
    if (cntPt <= midPt)
        update(leftSon, cntPt, val);
    else
        update(rightSon, cntPt, val);
    pushUp(segPt);
}

int query(int segPt, int leftPt, int rightPt)
{
    if (segTree[segPt].leftPt >= leftPt && segTree[segPt].rightPt <= rightPt)
    {
        return segTree[segPt].maxLoyalty;
    }

    int ans = -1;
    int midPt = (segTree[segPt].leftPt + segTree[segPt].rightPt) >> 1;
    if (leftPt <= midPt)
        ans = max(ans, query(leftSon, leftPt, rightPt));
    if (rightPt > midPt)
        ans = max(ans, query(rightSon, leftPt, rightPt));
    return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    int caseNum;
    cin >> caseNum;
    while (caseNum--)
    {
        memset(head, -1, sizeof(head));
        arrPt = 0;
        mp.clear();
        int personNum, oprNum;
        cin >> personNum >> oprNum;
        for (int i = 1; i < personNum; i++)
        {
            int parent;
            cin >> parent;
            addEdge(parent, i);
            cin >> empArr[i].loyalty >> empArr[i].ability;
            empArr[i].id = i;
            mp[empArr[i].loyalty] = i;
        }

        cntTime = 0;
        dfs(0);

        // time = 0 && time = cntTime aren't used anyway
        build(1, 1, cntTime - 1);
        sort(empArr + 1, empArr + personNum, cmpRule);

        for (int i = 1, j; i < personNum; i = j)
        {
            j = i;
            while (j < personNum && empArr[i].ability == empArr[j].ability)
            {
                int cntId = empArr[j].id;
                int maxLoyalty = query(1, inTime[cntId] + 1, outTime[cntId] - 1);
                if (maxLoyalty == -1)
                    ansArr[cntId] = -1;
                else
                    ansArr[cntId] = mp[maxLoyalty];
                j++;
            }

            j = i;
            while (j < personNum && empArr[i].ability == empArr[j].ability)
            {
                int cntId = empArr[j].id;
                update(1, inTime[cntId], empArr[j].loyalty);
                j++;
            }
        }

        while (oprNum--)
        {
            int cnt;
            cin >> cnt;
            cout << ansArr[cnt] << endl;
        }
    }
    return 0;
}
