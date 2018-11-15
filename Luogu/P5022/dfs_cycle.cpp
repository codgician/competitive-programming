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

#define SIZE 5010

vector<pair<int, int> > banArr;
pair<int, int> banEdge;

vector<int> arr[SIZE];
vector<int> ans, cntAns;

int vertexNum, edgeNum;

stack<int> stk;
bool hasVisited[SIZE], inStack[SIZE];

void addEdge(int from, int to)
{
    arr[from].push_back(to);
}

void dfs1(int cntPt, int prevPt)
{
    hasVisited[cntPt] = true;
    inStack[cntPt] = true;
    stk.push(cntPt);

    for (auto it = arr[cntPt].begin(); it != arr[cntPt].end(); ++it)
    {
        int nextPt = *it;
        if (nextPt == prevPt)
            continue;
        if (hasVisited[nextPt] && !inStack[nextPt])
            continue;
        if (hasVisited[nextPt])
        {
            if (stk.empty())
                continue;

            int topPt = -1;
            if (!stk.empty())
            {
                topPt = stk.top();
                inStack[topPt] = false;
                stk.pop();
            }

            int lastPt = topPt;
            while (!stk.empty())
            {
                int cntTop = stk.top();
                stk.pop();
                inStack[cntTop] = false;
                
                int fstPt = min(lastPt, cntTop);
                int sndPt = max(lastPt, cntTop);
                banArr.push_back(make_pair(fstPt, sndPt));
                lastPt = cntTop;

                if (cntTop == nextPt)
                    break;
            }

            if (topPt != lastPt)
            {
                int fstPt = min(topPt, lastPt);
                int sndPt = max(topPt, lastPt);
                banArr.push_back(make_pair(fstPt, sndPt));
            }
        } 
        else
        {
            dfs1(nextPt, cntPt);
        }
    }

    if (!stk.empty() && stk.top() == cntPt)
    {
        stk.pop();
        inStack[cntPt] = false;
    }
}

void dfs2(int cntPt, int prevPt)
{
    cntAns.push_back(cntPt);
    for (auto it = arr[cntPt].begin(); it != arr[cntPt].end(); ++it)
    {
        int nextPt = *it;
        if (nextPt == prevPt)
            continue;
        if (min(cntPt, nextPt) == banEdge.first && max(cntPt, nextPt) == banEdge.second)
            continue;
        dfs2(nextPt, cntPt);
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> vertexNum >> edgeNum;
    for (int i = 0; i < vertexNum; i++)
        arr[i].clear();
    for (int i = 0; i < edgeNum; i++)
    {
        int from, to;
        cin >> from >> to;
        from--, to--;
        addEdge(from, to);
        addEdge(to, from);
    }

    for (int i = 0; i < vertexNum; i++)
        sort(arr[i].begin(), arr[i].end());

    if (vertexNum == edgeNum + 1)
    {
        banEdge = make_pair(-1, -1);
        dfs2(0, -1);
        ans = cntAns;
    }
    else
    {
        banArr.clear();
        memset(hasVisited, false, sizeof(hasVisited));
        memset(inStack, false, sizeof(inStack));
        dfs1(0, -1);

        for (auto it = banArr.begin(); it != banArr.end(); ++it)
        {
            banEdge = *it;
            cntAns.clear();
            dfs2(0, -1);
            if (ans.empty())
                ans = cntAns;
            else
                ans = min(ans, cntAns);
        }
    }

    for (int i = 0; i < (int)ans.size(); i++)
    {
        cout << ans[i] + 1;
        if (i < (int)ans.size() - 1)
            cout << " ";
        else
            cout << endl;
    }

    return 0;
}