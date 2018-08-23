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
#include <bitset>
#include <functional>
#include <iterator>
using namespace std;

#define VERTEX_SIZE 100010
#define EDGE_SIZE 100010

typedef struct _Edge
{
    int to;
    int next;
} Edge;

Edge arr[EDGE_SIZE];
int head[VERTEX_SIZE], arrPt;
int vertexNum;

vector<int> divisorArr[VERTEX_SIZE];
set<int> *stArr[VERTEX_SIZE];

int val[VERTEX_SIZE], ans[VERTEX_SIZE];

void addEdge(int from, int to)
{
    arr[arrPt] = {to, head[from]};
    head[from] = arrPt++;
}

int mergeSet(int fst, int snd)
{
    int ans = INT_MIN;
    if ((*stArr[fst]).size() < (*stArr[snd]).size())
        swap(stArr[fst], stArr[snd]);

    for (auto it = (*stArr[snd]).begin(); it != (*stArr[snd]).end(); ++it)
    {
        if ((*stArr[fst]).find(*it) != (*stArr[fst]).end())
        {
            ans = max(ans, *it);
        }
        else
        {
            (*stArr[fst]).insert(*it);
        }
    }

    return ans;
}

void dfs(int cntPt)
{
    stArr[cntPt] = new set<int>();
    for (int i = 0; i < (int)divisorArr[val[cntPt]].size(); i++)
    {
        (*stArr[cntPt]).insert(divisorArr[val[cntPt]][i]);
    }

    for (int i = head[cntPt]; i != -1; i = arr[i].next)
    {
        int nextPt = arr[i].to;
        dfs(nextPt);
        ans[cntPt] = max(ans[cntPt], mergeSet(cntPt, nextPt));

        delete stArr[nextPt];
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    for (int i = 1; i < VERTEX_SIZE; i++)
    {
        for (int j = i; j < VERTEX_SIZE; j += i)
        {
            divisorArr[j].push_back(i);
        }
    }

    while (cin >> vertexNum)
    {
        memset(head, -1, sizeof(head));
        for (int i = 1; i < vertexNum; i++)
        {
            int cntFather;
            cin >> cntFather;
            cntFather--;
            addEdge(cntFather, i);
        }

        for (int i = 0; i < vertexNum; i++)
        {
            cin >> val[i];
            ans[i] = -1;
        }

        dfs(0);

        for (int i = 0; i < vertexNum; i++)
        {
            cout << ans[i] << endl;
        }
    }
    return 0;
}