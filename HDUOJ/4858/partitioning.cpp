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
#include <map>
#include <set>
#include <stack>
#include <functional>
#include <iterator>
#define EDGE_SIZE 200200
#define VERTEX_SIZE 100100
using namespace std;

typedef struct _Edge
{
    int to;
    int len;
    int next;
} Edge;

Edge arr[EDGE_SIZE];
int head[VERTEX_SIZE], arrPt;

long long int valArr[VERTEX_SIZE];
int degArr[VERTEX_SIZE];
map<pair<int, int>, int> mp;

long long int heavySum[VERTEX_SIZE];
bool isHeavy[VERTEX_SIZE];

int lim, vertexNum, edgeNum;

void addEdge(int from, int to, int len)
{
    arr[arrPt] = {to, len, head[from]};
    head[from] = arrPt++;
}

void updateNode(int cntPt, long long int val)
{
    for (int i = head[cntPt]; i != -1; i = arr[i].next)
    {
        int nextPt = arr[i].to;
        int len = arr[i].len;

        if (isHeavy[nextPt])
        {
            heavySum[nextPt] += val * len;
        }
    }
    valArr[cntPt] += val;
}

long long int getSum(int cntPt)
{
    long long int ans = 0;
    if (isHeavy[cntPt])
    {
        ans = heavySum[cntPt];
    }
    else
    {
        for (int i = head[cntPt]; i != -1; i = arr[i].next)
        {
            int nextPt = arr[i].to;
            int len = arr[i].len;

            ans += len * valArr[nextPt];
        }
    }

    return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    int caseNum;
    cin >> caseNum;
    while (caseNum--)
    {
        mp.clear();
        memset(head, -1, sizeof(head));
        memset(valArr, 0, sizeof(valArr));
        memset(degArr, 0, sizeof(degArr));
        memset(heavySum, 0, sizeof(heavySum));
        arrPt = 0;

        cin >> vertexNum >> edgeNum;
        lim = sqrt(vertexNum);

        for (int i = 0; i < edgeNum; i++)
        {
            int from, to;
            cin >> from >> to;
            from--;
            to--;
            mp[make_pair(from, to)]++;
            degArr[from]++;
            degArr[to]++;
        }

        for (int i = 0; i < vertexNum; i++)
        {
            if (degArr[i] >= lim)
            {
                isHeavy[i] = true;
            }
            else
            {
                isHeavy[i] = false;
            }
        }

        for (map<pair<int, int>, int>::iterator it = mp.begin(); it != mp.end(); it++)
        {
            int from = (it -> first).first;
            int to = (it -> first).second;
            int len = it -> second;

            if (isHeavy[from] && isHeavy[to])
            {
                addEdge(from, to, len);
                addEdge(to, from, len);
            }
            else if (!isHeavy[from] && !isHeavy[to])
            {
                addEdge(from, to, len);
                addEdge(to, from, len);
            }
            else if (isHeavy[from])
            {
                addEdge(to, from, len);
            }
            else
            {
                addEdge(from, to, len);
            }
        }

        int qNum;
        cin >> qNum;
        while (qNum--)
        {
            bool opr;
            cin >> opr;
            if (opr == 0)
            {
                int id;
                long long int val;
                cin >> id >> val;
                id--;
                updateNode(id, val);
            }
            else
            {
                int id;
                cin >> id;
                id--;

                long long int ans = getSum(id);
                cout << ans << endl;
            }
        }
    }
    return 0;
}