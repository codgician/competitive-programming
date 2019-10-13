#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <string>
#include <climits>
#include <iomanip>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <stack>
#include <functional>
#include <iterator>
#define VERTEX_NUM 1010
#define EDGE_NUM 2020
using namespace std;

typedef struct _Edge
{
    int to;
    int len;
    int next;
} Edge;

Edge arr[EDGE_NUM];
int head[VERTEX_NUM], arrPt;

int dis[VERTEX_NUM], cnt[VERTEX_NUM];
bool isInQueue[VERTEX_NUM];

int needTime[VERTEX_NUM];

int vertexNum;

void addEdge(int from, int to, int len)
{
    arr[arrPt] = {to, len, head[from]};
    head[from] = arrPt++;
}

bool spfa(int startPt)
{
    memset(isInQueue, false, sizeof(isInQueue));
    for (int i = 0; i < vertexNum; i++)
        dis[i] = INT_MAX;
    
    queue<int> q;
    for (int i = 0; i < vertexNum; i++)
    {
        q.push(i);
        cnt[i] = 0;
        dis[i] = 0;
        isInQueue[i] = true;
    }
    
    while (!q.empty())
    {
        int cntPt = q.front();
        q.pop();
        isInQueue[cntPt] = false;

        for (int i = head[cntPt]; i != -1; i = arr[i].next)
        {
            int nextPt = arr[i].to;
            if (dis[cntPt] != INT_MAX && dis[nextPt] > dis[cntPt] + arr[i].len)
            {
                dis[nextPt] = dis[cntPt] + arr[i].len;
                cnt[nextPt] = cnt[cntPt] + 1;

                if (cnt[nextPt] >= vertexNum)
                {
                    return false;
                }

                if (!isInQueue[nextPt])
                {
                    q.push(nextPt);
                    isInQueue[nextPt] = true;
                }
            }
        }
    }

    return true;
}

int main()
{
    ios::sync_with_stdio(false);
    int partNum, casePt = 0;
    while (cin >> partNum)
    {
        if (partNum == 0)
            break;

        memset(head, -1, sizeof(head));
        arrPt = 0;

        for (int i = 0; i < partNum; i++)
        {
            cin >> needTime[i];
        }

        string str;
        while (cin >> str)
        {
            if (str[0] == '#')
                break;

            int fst, snd;
            cin >> fst >> snd;
            fst--;
            snd--;

            if (str == "FAS")
            {
                addEdge(fst, snd, needTime[fst]);
            }
            else if (str == "FAF")
            {
                addEdge(fst, snd, needTime[fst] - needTime[snd]);
            }
            else if (str == "SAF")
            {
                addEdge(fst, snd, -needTime[snd]);
            }
            else if (str == "SAS")
            {
                addEdge(fst, snd, 0);
            }
        }

        cout << "Case " << ++casePt << ":" << endl;
        vertexNum = partNum;
        if (spfa(0))
        {
            int minVal = INT_MAX;
            for (int i = 0; i < vertexNum; i++)
            {
                if (minVal > dis[i])
                {
                    minVal = dis[i];
                }
            }

            for (int i = 0; i < vertexNum; i++)
            {
                cout << i + 1 << " " << dis[i] - minVal << endl;
            }
        }
        else
        {
            cout << "impossible" << endl;
        }
        cout << endl;
    }
    return 0;
}