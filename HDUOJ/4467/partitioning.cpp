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
#define VERTEX_SIZE 100100
#define EDGE_SIZE 200200
using namespace std;

typedef struct _Edge
{
    int to;
    long long int len;
    int next;
} Edge;

Edge arr[2][EDGE_SIZE];
int head[2][VERTEX_SIZE], arrPt[2];

int colorArr[VERTEX_SIZE];
int degArr[VERTEX_SIZE];

map<pair<int, int>, long long int> mp;
int heavyId[VERTEX_SIZE], heavyPt;

long long int heavySum[VERTEX_SIZE][2];

long long int ans[3];

int vertexNum, edgeNum, lim;

void addEdge(int id, int from, int to, long long int len)
{
    arr[id][arrPt[id]] = {to, len, head[id][from]};
    head[id][from] = arrPt[id]++;
}

void updateColor(int cntPt)
{
    if (heavyId[cntPt] > -1)
    {
        for (int i = 0; i < 2; i++)
        {
            ans[colorArr[cntPt] + i] -= heavySum[heavyId[cntPt]][i];
            ans[!colorArr[cntPt] + i] += heavySum[heavyId[cntPt]][i]; 
        }

        for (int i = head[1][heavyId[cntPt]]; i != -1; i = arr[1][i].next)
        {
            int nextHeavyPt = arr[1][i].to;
            long long int len = arr[1][i].len;

            heavySum[nextHeavyPt][colorArr[cntPt]] -= len;
            heavySum[nextHeavyPt][!colorArr[cntPt]] += len;
        }
    }
    else
    {
        for (int i = head[0][cntPt]; i != -1; i = arr[0][i].next)
        {
            int nextPt = arr[0][i].to;
            long long int len = arr[0][i].len;

            ans[colorArr[cntPt] + colorArr[nextPt]] -= len;
            ans[!colorArr[cntPt] + colorArr[nextPt]] += len;

            if (heavyId[nextPt] > -1)
            {
                heavySum[heavyId[nextPt]][colorArr[cntPt]] -= len;
                heavySum[heavyId[nextPt]][!colorArr[cntPt]] += len;
            }
        }
    }

    colorArr[cntPt] = !colorArr[cntPt];
}

int main()
{
    int casePt = 0;
    while (scanf("%d%d", &vertexNum, &edgeNum) != EOF)
    {
        mp.clear();
        memset(head, -1, sizeof(head));
        memset(arrPt, 0, sizeof(arrPt));
        memset(degArr, 0, sizeof(degArr));
        memset(heavyId, -1, sizeof(heavyId));
        memset(heavySum, 0, sizeof(heavySum));
        memset(ans, 0, sizeof(ans));
        
        lim = sqrt(vertexNum);

        for (int i = 0; i < vertexNum; i++)
        {
            scanf("%d", colorArr + i);
        }

        for (int i = 0; i < edgeNum; i++)
        {
            int from, to;
            long long int len;
            scanf("%d%d%lld", &from, &to, &len);
            from--;
            to--;
            if (from > to)
                swap(from, to);

            mp[make_pair(from, to)] += len;
            ans[colorArr[from] + colorArr[to]] += len;
            degArr[from]++;
            degArr[to]++;
        }

        heavyPt = 0;
        for (int i = 0; i < vertexNum; i++)
        {
            if (degArr[i] >= lim)
            {
                heavyId[i] = heavyPt++;
            }
        }

        for (map<pair<int, int>, long long int>::iterator it = mp.begin(); it != mp.end(); it++)
        {
            int from = (it -> first).first;
            int to = (it -> first).second;
            long long int len = it -> second;

            if (heavyId[from] > -1 && heavyId[to] > -1)
            {
                addEdge(1, heavyId[from], heavyId[to], len);
                addEdge(1, heavyId[to], heavyId[from], len);
                heavySum[heavyId[from]][colorArr[to]] += len;
                heavySum[heavyId[to]][colorArr[from]] += len;
            }
            else if (heavyId[from] == -1 && heavyId[to] == -1)
            {
                addEdge(0, from, to, len);
                addEdge(0, to, from, len);
            }
            else if (heavyId[from] > -1)
            {
                heavySum[heavyId[from]][colorArr[to]] += len;
                addEdge(0, to, from, len);
            }
            else
            {
                heavySum[heavyId[to]][colorArr[from]] += len;
                addEdge(0, from, to, len);
            }
        }
        
        printf("Case %d:\n", ++casePt);
        int qNum;
        scanf("%d", &qNum);
        while (qNum--)
        {
            char opr[10];
            scanf("%s", opr);

            if (opr[0] == 'C')
            {
                int cnt;
                scanf("%d", &cnt);
                cnt--;
                updateColor(cnt);
            }
            else
            {
                int fst, snd;
                scanf("%d%d", &fst, &snd);
                printf("%lld\n", ans[fst + snd]);
            }
        }
    }
    return 0;
}