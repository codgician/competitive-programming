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

#define LEFT_SON (segPt << 1)
#define RIGHT_SON (segPt << 1 | 1)
#define SIZE 500010

typedef struct _Query
{
    int id;
    int qLeftPt, qRightPt;
} Query;

Query qArr[SIZE];
int ans[SIZE];

typedef struct _SegNode
{
    pair<int, int> minPt;   // last, pos
    int leftPt, rightPt;
} SegNode;

SegNode segTree[SIZE << 2];

int arr[SIZE];
int pre[SIZE];

bool cmpRule(Query & fst, Query & snd)
{
    return fst.qRightPt < snd.qRightPt;
}

void pushUp(int segPt)
{
    segTree[segPt].minPt = min(segTree[LEFT_SON].minPt, segTree[RIGHT_SON].minPt);
}

void build(int segPt, int leftPt, int rightPt)  // build blank tree
{
    segTree[segPt].leftPt = leftPt;
    segTree[segPt].rightPt = rightPt;

    if (leftPt == rightPt)
    {
        return;
    }

    int midPt = (leftPt + rightPt) >> 1;
    build(LEFT_SON, leftPt, midPt);
    build(RIGHT_SON, midPt + 1, rightPt);
}

void update(int segPt, int pos, int val)
{
    if (segTree[segPt].leftPt == segTree[segPt].rightPt)
    {
        segTree[segPt].minPt = make_pair(val, pos);
        return;
    }

    int midPt = (segTree[segPt].leftPt + segTree[segPt].rightPt) >> 1;
    if (pos <= midPt)
        update(LEFT_SON, pos, val);
    else
        update(RIGHT_SON, pos, val);
    pushUp(segPt);
}

pair<int, int> query(int segPt, int qLeftPt, int qRightPt)
{
    if (qLeftPt <= segTree[segPt].leftPt && qRightPt >= segTree[segPt].rightPt)
    {
        return segTree[segPt].minPt;
    }

    pair<int, int> ans = make_pair(INT_MAX, -1);
    int midPt = (segTree[segPt].leftPt + segTree[segPt].rightPt) >> 1;
    if (qLeftPt <= midPt)
        ans = min(ans, query(LEFT_SON, qLeftPt, qRightPt));
    if (qRightPt > midPt)
        ans = min(ans, query(RIGHT_SON, qLeftPt, qRightPt));
    return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    int len;
    cin >> len;

    for (int i = 1; i <= len; i++)
    {
        cin >> arr[i];
    }

    int qNum;
    cin >> qNum;
    for (int i = 1; i <= qNum; i++)
    {
        cin >> qArr[i].qLeftPt >> qArr[i].qRightPt;
        qArr[i].id = i;
    }
    sort(qArr + 1, qArr + qNum + 1, cmpRule);

    build(1, 1, len);

    memset(ans, 0, sizeof(ans));
    memset(pre, 0, sizeof(pre));
    qArr[0].qRightPt = 0;
    for (int i = 1; i <= qNum; i++)
    {
        if (qArr[i].qRightPt != qArr[i - 1].qRightPt)
        {
            for (int j = qArr[i - 1].qRightPt + 1; j <= qArr[i].qRightPt; j++)
            {
                if (pre[arr[j]])
                    update(1, pre[arr[j]], INT_MAX);
                update(1, j, pre[arr[j]]);
                pre[arr[j]] = j;
            }
        }

        pair<int, int> cntAns = query(1, qArr[i].qLeftPt, qArr[i].qRightPt);
        if (cntAns.first < qArr[i].qLeftPt)
            ans[qArr[i].id] = arr[cntAns.second];
    }

    for (int i = 1; i <= qNum; i++)
    {
        cout << ans[i] << endl;
    }

    return 0;
}