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

bitset<VERTEX_SIZE> *bstArr[VERTEX_SIZE];
vector<int> divisorArr[VERTEX_SIZE];

int val[VERTEX_SIZE], ans[VERTEX_SIZE];

void addEdge(int from, int to)
{
    arr[arrPt] = {to, head[from]};
    head[from] = arrPt++;
}

void dfs(int cntPt)
{
    bstArr[cntPt] = new bitset<VERTEX_SIZE>(0);
    for (int i = 0; i < (int)divisorArr[val[cntPt]].size(); i++)
    {
        (*bstArr[cntPt])[VERTEX_SIZE - 1 - divisorArr[val[cntPt]][i]] = 1;
    }

    for (int i = head[cntPt]; i != -1; i = arr[i].next)
    {
        int nextPt = arr[i].to;

        dfs(nextPt);

        int maxDivisor = ((*bstArr[cntPt]) & (*bstArr[nextPt]))._Find_first();
        *bstArr[cntPt] |= *bstArr[nextPt];
        ans[cntPt] = max(ans[cntPt], VERTEX_SIZE - 1 - maxDivisor);

        delete bstArr[nextPt];
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