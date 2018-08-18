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

#define SIZE 200020

const int mod = 998244353;

typedef struct _Edge
{
    int to;
    bool dir, visited;
    int next;
} Edge;

Edge arr[SIZE << 1];
int head[SIZE], arrPt;

int parent[SIZE];

int deg[SIZE], wccSize[SIZE];

bool hasVisited[SIZE];

int minRev, cntRev, wayNum;
int cycleArr[SIZE], cycleSize, cycleNextPt;

void addEdge(int from, int to, bool dir)
{
    arr[arrPt] = {to, dir, false, head[from]};
    head[from] = arrPt++;
}

int getParent(int n)
{
    if (parent[n] == n)
        return n;
    else
    {
        parent[n] = getParent(parent[n]);
        return parent[n];
    }
}

void mergeNode(int fst, int snd)
{
    int fstParent = getParent(fst);
    int sndParent = getParent(snd);

    if (fstParent != sndParent)
    {
        parent[sndParent] = fstParent;
    }
}

void dfs1(int cntPt, int fatherPt)
{
    for (int i = head[cntPt]; i != -1; i = arr[i].next)
    {
        int nextPt = arr[i].to;
        if (nextPt == fatherPt)
            continue;

        dfs1(nextPt, cntPt);

        if (arr[i].dir == 0)
            cntRev++; 
    }
}

void dfs2(int cntPt, int fatherPt)
{
    if (cntRev < minRev)
    {
        minRev = cntRev;
        wayNum = 1;
    }
    else if (cntRev == minRev)
    {
        wayNum++;
    }

    for (int i = head[cntPt]; i != -1; i = arr[i].next)
    {
        int nextPt = arr[i].to;
        if (nextPt == fatherPt)
            continue;

        if (arr[i].dir == 1)
            cntRev++;
        else
            cntRev--;

        dfs2(nextPt, cntPt);

        if (arr[i].dir == 1)
            cntRev--;
        else
            cntRev++;
    }
}

void dfs3(int cntPt)
{
    hasVisited[cntPt] = true;
    for (int i = head[cntPt]; i != -1; i = arr[i].next)
    {
        int nextPt = arr[i].to;
        if (!arr[i].visited)
        {
            arr[i].visited = true;
            arr[i ^ 1].visited = true;

            if (hasVisited[nextPt])
            {
                cycleNextPt = nextPt;
                cycleArr[cycleSize++] = cntPt;
                break;
            }
            else
            {
                dfs3(nextPt);
            }

            if (cycleNextPt != -1)
            {
                cycleArr[cycleSize++] = cntPt;
                break;
            }
        }
    }

    if (cycleNextPt == cntPt)
        cycleNextPt = -1;
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
        memset(deg, 0, sizeof(deg));
        memset(wccSize, 0, sizeof(wccSize));
        memset(hasVisited, false, sizeof(hasVisited));
        arrPt = 0;

        int cardNum;
        cin >> cardNum;

        for (int i = 0; i < (cardNum << 1); i++)
        {
            parent[i] = i;
        }

        for (int i = 0; i < cardNum; i++)
        {
            int front, back;
            cin >> front >> back;
            front--;
            back--;
            deg[front]++;
            deg[back]++;
            addEdge(back, front, 1);
            addEdge(front, back, 0);
            mergeNode(front, back);
        }

        for (int i = 0; i < (cardNum << 1); i++)
        {
            if (getParent(i) != i)
            {
                deg[getParent(i)] += deg[i];
                wccSize[getParent(i)]++;
            }
        }

        int ans1 = 0;
        long long int ans2 = 1;
        for (int i = 0; i < (cardNum << 1); i++)
        {
            if (getParent(i) == i)
            {
                wccSize[i]++;
                minRev = INT_MAX;
                cntRev = 0;
                wayNum = 0;

                if ((deg[i] >> 1) == wccSize[i] - 1)
                {
                    // Tree
                    dfs1(i, -1);
                    dfs2(i, -1);
                }
                else if ((deg[i] >> 1) == wccSize[i])
                {
                    // Tree with cycle
                    cycleSize = 0;
                    cycleNextPt = -1;
                    dfs3(i);

                    for (int j = 0; j < cycleSize; j++)
                    {
                        for (int k = head[cycleArr[j]]; k != -1; k = arr[k].next)
                        {
                            int nextPt = arr[k].to;
                            if (nextPt == cycleArr[(j + 1) % cycleSize] && arr[k].dir == 1)
                            {
                                cntRev++;
                                break;
                            }
                        }
                    }

                    cntRev = min(cntRev, cycleSize - cntRev);
                    wayNum = 1;
                    if ((cntRev << 1) == cycleSize)
                    {
                        wayNum = 2;
                    }

                    for (int j = 0; j < cycleSize; j++)
                    {
                        for (int k = head[cycleArr[j]]; k != -1; k = arr[k].next)
                        {
                            int nextPt = arr[k].to;
                            if (nextPt != cycleArr[(j - 1 + cycleSize) % cycleSize] && 
                                nextPt != cycleArr[(j + 1) % cycleSize])
                            {
                                dfs1(nextPt, cycleArr[j]);
                                if (arr[k].dir == 0)
                                {
                                    cntRev++;
                                }
                            }
                        }
                    }
                    minRev = cntRev;
                }

                if (minRev != INT_MAX)
                {
                    ans2 *= wayNum;
                    if (ans2 >= mod)
                        ans2 %= mod;
                    ans1 += minRev;
                }
                else
                {
                    ans1 = -1;
                    ans2 = -1;
                    break;
                }
            }
        }
        cout << ans1 << " " << ans2 << endl;
    }
    return 0;
}