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

#define SIZE 100010

#define LEFT_SON (segPt << 1)
#define RIGHT_SON (segPt << 1 | 1)

typedef struct _Node
{
    pair<int, int> maxVal[2], secMaxVal[2];
    pair<int, int> minVal[2], secMinVal[2];

    void init()
    {
        for (int i = 0; i < 2; i++)
        {
            maxVal[i] = make_pair(INT_MIN, INT_MIN), secMaxVal[i] = make_pair(INT_MIN, INT_MIN);
            minVal[i] = make_pair(INT_MAX, INT_MAX), secMinVal[i] = make_pair(INT_MAX, INT_MAX);
        }
    }
} Node;

int arr[SIZE][2];

typedef struct _SegNode
{
    int leftPt, rightPt;
    Node data;
} SegNode;

SegNode segTree[SIZE << 2];

Node mergeNode(const Node & fst, const Node & snd)
{
    Node ret;
    ret.init();

    // Maximum and minimum
    for (int i = 0; i < 2; i++)
    {
        ret.maxVal[i] = max(fst.maxVal[i], snd.maxVal[i]);
        ret.minVal[i] = min(fst.minVal[i], snd.minVal[i]);
    }

    // Secondary maximum
    for (int i = 0; i < 2; i++)
    {
        if (ret.maxVal[i] == fst.maxVal[i])
            ret.secMaxVal[i] = max(snd.maxVal[i], max(fst.secMaxVal[i], snd.secMaxVal[i]));
        else
            ret.secMaxVal[i] = max(fst.maxVal[i], max(fst.secMaxVal[i], snd.secMaxVal[i]));
    }

    // Secondary minimum
    for (int i = 0; i < 2; i++)
    {
        if (ret.minVal[i] == fst.minVal[i])
            ret.secMinVal[i] = min(snd.minVal[i], min(fst.secMinVal[i], snd.secMinVal[i]));
        else
            ret.secMinVal[i] = min(fst.minVal[i], min(fst.secMinVal[i], snd.secMinVal[i]));
    }

    return ret;
}

void pushUp(int segPt)
{
    segTree[segPt].data = mergeNode(segTree[LEFT_SON].data, segTree[RIGHT_SON].data);    
}

void build(int segPt, int leftPt, int rightPt)
{
    segTree[segPt].leftPt = leftPt;
    segTree[segPt].rightPt = rightPt;

    if (leftPt == rightPt)
    {
        for (int i = 0; i < 2; i++)
        {
            segTree[segPt].data.maxVal[i] = make_pair(arr[leftPt][i], arr[leftPt][i ^ 1]);
            segTree[segPt].data.minVal[i] = make_pair(arr[leftPt][i], arr[leftPt][i ^ 1]);
            segTree[segPt].data.secMaxVal[i] = make_pair(INT_MIN, INT_MIN);
            segTree[segPt].data.secMinVal[i] = make_pair(INT_MAX, INT_MAX);
        }
        return;
    }

    int midPt = (leftPt + rightPt) >> 1;
    build(LEFT_SON, leftPt, midPt);
    build(RIGHT_SON, midPt + 1, rightPt);
    pushUp(segPt);
}

Node query(int segPt, int qLeftPt, int qRightPt)
{
    if (segTree[segPt].leftPt >= qLeftPt && segTree[segPt].rightPt <= qRightPt)
    {
        return segTree[segPt].data;
    }

    Node ans;
    ans.init();
    int midPt = (segTree[segPt].leftPt + segTree[segPt].rightPt) >> 1;
    if (qLeftPt <= midPt)
        ans = mergeNode(ans, query(LEFT_SON, qLeftPt, qRightPt));
    if (qRightPt > midPt)
        ans = mergeNode(ans, query(RIGHT_SON, qLeftPt, qRightPt));
    return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int len, qNum;
    while (cin >> len >> qNum)
    {

        for (int i = 1; i <= len; i++)
        {
            for (int j = 0; j < 2; j++)
            {
                cin >> arr[i][j];
            }
        }

        build(1, 1, len);
        
        while (qNum--)
        {
            int qLeftPt, qRightPt;
            cin >> qLeftPt >> qRightPt;

            if (qRightPt - qLeftPt == 1)
            {
                cout << 0 << endl;
                continue;
            }

            Node ret = query(1, qLeftPt, qRightPt);

            //ret.log();

            int orig[2], ans = INT_MIN;
            for (int i = 0; i < 2; i++)
            {
                orig[i] = ret.maxVal[i].first - ret.minVal[i].first;
                ans = max(ans, orig[i]);
            }

            for (int id = 0; id < 2; id++)
            {
                if (orig[id] != ans)
                    continue;

                int fstAns, sndAns;

                // Ignore id.minVal
                if (ret.minVal[id].second == ret.maxVal[id ^ 1].first && ret.maxVal[id ^ 1].first != ret.secMaxVal[id ^ 1].first)
                {
                    // If id.minVal pt is also the ONLY [id ^ 1].maxVal
                    fstAns = max(ret.maxVal[id].first - ret.secMinVal[id].first, ret.secMaxVal[id ^ 1].first - ret.minVal[id ^ 1].first);
                }
                else if (ret.minVal[id].second == ret.minVal[id ^ 1].first && ret.minVal[id ^ 1].first != ret.secMinVal[id ^ 1].first)
                {
                    // If id.minVal pt is also the ONLY [id ^ 1].minVal
                    fstAns = max(ret.maxVal[id].first - ret.secMinVal[id].first, ret.maxVal[id ^ 1].first - ret.secMinVal[id ^ 1].first);
                }
                else
                {
                    // Otherwise
                    fstAns = max(orig[id ^ 1], ret.maxVal[id].first - ret.secMinVal[id].first);
                }

                // Ignore id.maxVal
                if (ret.maxVal[id].second == ret.maxVal[id ^ 1].first && ret.maxVal[id ^ 1].first != ret.secMaxVal[id ^ 1].first)
                {
                    // If id.maxVal pt is also the ONLY [id ^ 1].maxVal
                    sndAns = max(ret.secMaxVal[id].first - ret.minVal[id].first, ret.secMaxVal[id ^ 1].first - ret.minVal[id ^ 1].first);
                }
                else if (ret.maxVal[id].second == ret.minVal[id ^ 1].first && ret.minVal[id ^ 1].first != ret.secMinVal[id ^ 1].first)
                {
                    // If id.maxVal pt is also the ONLY [id ^ 1].minVal
                    sndAns = max(ret.secMaxVal[id].first - ret.minVal[id].first, ret.maxVal[id ^ 1].first - ret.secMinVal[id ^ 1].first);
                }
                else
                {
                    // Otherwise
                    sndAns = max(orig[id ^ 1], ret.secMaxVal[id].first - ret.minVal[id].first);
                }

                ans = min(ans, min(fstAns, sndAns));
            }

            cout << ans << endl;
        }
    }

    return 0;
}