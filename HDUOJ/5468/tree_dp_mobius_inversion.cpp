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
#include <cassert>
using namespace std;

#define SIZE 100010

typedef struct _Edge
{
    int to;
    int next;
} Edge;

Edge arr[SIZE << 1];
int head[SIZE], arrPt;
int valArr[SIZE], vertexNum;

int primeArr[SIZE], minFacArr[SIZE], mu[SIZE], primePt;
vector<int> facArr[SIZE];

int ansArr[SIZE], countArr[SIZE];

void initMu()
{
    memset(minFacArr, 0, sizeof(minFacArr));
    primePt = 0;
    mu[1] = 1;
    for (int i = 2; i < SIZE; i++)
    {
        if (minFacArr[i] == 0)
        {
            minFacArr[i] = i;
            mu[i] = -1;
            primeArr[primePt++] = i;
        }

        for (int j = 0; j < primePt && primeArr[j] <= minFacArr[i] && primeArr[j] <= (SIZE - 1) / i ;j++)
        {
            minFacArr[i * primeArr[j]] = primeArr[j];
            if (minFacArr[i] == primeArr[j])
                mu[i * primeArr[j]] = 0;
            else
                mu[i * primeArr[j]] = -mu[i];
        }
    }
}

void initFac()
{
    for (int i = 1; i < SIZE; i++)
    {
        if (mu[i] == 0)
            continue;
        for (int j = 1; i * j < SIZE; j++)
        {
            facArr[i * j].push_back(i);
        }
    }
}

void addEdge(int from, int to)
{
    arr[arrPt] = {to, head[from]};
    head[from] = arrPt++;
}

void dfs(int cntPt, int parentPt)
{
    vector<int> prevCountArr;
    for (int i = 0; i < (int)facArr[valArr[cntPt]].size(); i++)
    {
        int val = facArr[valArr[cntPt]][i];
        prevCountArr.push_back(countArr[val]++);
    }

    for (int i = head[cntPt]; i != -1; i = arr[i].next)
    {
        int nextPt = arr[i].to;
        if (nextPt == parentPt)
            continue;
        dfs(nextPt, cntPt);
    }

    ansArr[cntPt] = 0;
    for (int i = 0; i < (int)facArr[valArr[cntPt]].size(); i++)
    {
        int val = facArr[valArr[cntPt]][i];
        ansArr[cntPt] += mu[val] * (countArr[val] - prevCountArr[i]);
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    initMu();
    initFac();

    int casePt = 0;
    while (cin >> vertexNum)
    {
        memset(head, -1, sizeof(head));
        memset(ansArr, 0, sizeof(ansArr));
        memset(countArr, 0, sizeof(countArr));
        arrPt = 0;

        for (int i = 1; i < vertexNum; i++)
        {
            int from, to;
            cin >> from >> to;
            from--;
            to--;
            addEdge(from, to);
            addEdge(to, from);
        }

        for (int i = 0; i < vertexNum; i++)
        {
            cin >> valArr[i];
        }

        dfs(0, -1);

        cout << "Case #" << ++casePt << ":";
        for (int i = 0; i < vertexNum; i++)
            cout << " " << ansArr[i];
        cout << endl;
    }

    return 0;
}