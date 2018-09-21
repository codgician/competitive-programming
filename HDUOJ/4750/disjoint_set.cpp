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

#define VERTEX_SIZE 10010
#define EDGE_SIZE 500010
#define QUERY_SIZE 100010

typedef struct _Query
{
    int id;
    int len;
} Query;

Query qArr[QUERY_SIZE];
int ansArr[QUERY_SIZE];

typedef struct _Edge
{
    int from, to, len;
} Edge;

Edge arr[EDGE_SIZE];
int parentArr[VERTEX_SIZE], setSize[VERTEX_SIZE];

int getParent(int cnt)
{
    if (cnt == parentArr[cnt])
    {
        return cnt;
    }
    else
    {
        parentArr[cnt] = getParent(parentArr[cnt]);
        return parentArr[cnt];
    }
}

int mergeNode(int fst, int snd)
{
    int fstParent = getParent(fst);
    int sndParent = getParent(snd);

    if (fstParent > sndParent)
        swap(fstParent, sndParent);

    if (fstParent != sndParent)
    {
        int ret = (setSize[fstParent] * setSize[sndParent]) << 1;

        parentArr[sndParent] = fstParent;
        setSize[fstParent] += setSize[sndParent];

        return ret;
    }

    return 0;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int vertexNum, edgeNum;
    while (cin >> vertexNum >> edgeNum)
    {
        for (int i = 0; i < edgeNum; i++)
        {
            cin >> arr[i].from >> arr[i].to >> arr[i].len;
        }

        int qNum;
        cin >> qNum;
        for (int i = 0; i < qNum; i++)
        {
            qArr[i].id = i;
            cin >> qArr[i].len;
        }

        sort(arr + 0, arr + edgeNum, [](Edge & fst, Edge & snd) {
            return fst.len < snd.len;
        });
        sort(qArr + 0, qArr + qNum, [](Query & fst, Query & snd) {
            return fst.len < snd.len;
        });

        for (int i = 0; i < vertexNum; i++)
        {
            parentArr[i] = i;
            setSize[i] = 1;
        }

        int ans = 0, qPt = 0;
        for (int i = 0; i < edgeNum; i++)
        {
            while (qPt < qNum && arr[i].len >= qArr[qPt].len)
            {
                cout << "len = " << qArr[qPt].len << " ans = " << ans << endl;
                ansArr[qArr[qPt].id] = ans;
                qPt++;
            }

            ans += mergeNode(arr[i].from, arr[i].to);
        }

        while (qPt < qNum)
        {
            ansArr[qArr[qPt].id] = ans;
            qPt++;
        }

        for (int i = 0; i < qNum; i++)
        {
            cout << ans - ansArr[i] << endl;
        }
    }

    return 0;
}