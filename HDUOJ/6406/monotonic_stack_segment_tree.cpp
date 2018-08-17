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

int arr[SIZE];
int startFrom[SIZE];
pair<int, int> endAt[SIZE];

class MonoStack
{
private:
    int pt;
    int arr[SIZE];

public:
    MonoStack()
    {
        pt = 0;
    }

    bool empty()
    {
        return pt == 0;
    }

    int size()
    {
        return pt;
    }

    int top()
    {
        return arr[pt - 1];
    }

    void pop()
    {
        pt--;
    }

    void push(int val)
    {
        while (!empty() && top() <= val)
        {
            pop();
        }
        arr[pt++] = val;
    }
};

#define LEFT_SON (segPt << 1)
#define RIGHT_SON (segPt << 1 | 1)

typedef struct _SegNode
{
    int leftPt, rightPt;
    int maxVal, maxPos;
} SegNode;

SegNode segTree[SIZE << 2];

void pushUp(int segPt)
{
    if (segTree[LEFT_SON].maxVal >= segTree[RIGHT_SON].maxVal)
    {
        segTree[segPt].maxVal = segTree[LEFT_SON].maxVal;
        segTree[segPt].maxPos = segTree[LEFT_SON].maxPos;
    }
    else
    {
        segTree[segPt].maxVal = segTree[RIGHT_SON].maxVal;
        segTree[segPt].maxPos = segTree[RIGHT_SON].maxPos;
    }
}

void build(int segPt, int leftPt, int rightPt)
{
    segTree[segPt].leftPt = leftPt;
    segTree[segPt].rightPt = rightPt;

    if (leftPt == rightPt)
    {
        segTree[segPt].maxVal = arr[leftPt];
        segTree[segPt].maxPos = leftPt;
        return;
    }

    int midPt = (leftPt + rightPt) >> 1;
    build(LEFT_SON, leftPt, midPt);
    build(RIGHT_SON, midPt + 1, rightPt);
    pushUp(segPt);
}


pair<int, int> query(int segPt, int qLeftPt, int qRightPt, int val)
{
    if (segTree[segPt].maxVal <= val)
        return make_pair(-1, -1);

    if (segTree[segPt].leftPt == segTree[segPt].rightPt)
    {
        return make_pair(segTree[segPt].maxVal, segTree[segPt].leftPt);
    }

    int midPt = (segTree[segPt].leftPt + segTree[segPt].rightPt) >> 1;
    if (qLeftPt <= midPt)
    {
        pair<int, int> res = query(LEFT_SON, qLeftPt, qRightPt, val);
        if (res.first != -1)
            return res;
    }

    if (qRightPt > midPt)
    {
        pair<int, int> res = query(RIGHT_SON, qLeftPt, qRightPt, val);
        if (res.first != -1)
            return res;
    }

    return make_pair(-1, -1);
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
        int len, qNum;
        cin >> len >> qNum;

        for (int i = 1; i <= len; i++)
        {
            cin >> arr[i];
        }

        endAt[0] = make_pair(0, 0);
        endAt[1] = make_pair(1, arr[1]);
        for (int i = 2; i <= len; i++)
        {
            endAt[i] = endAt[i - 1];
            if (arr[i] > endAt[i - 1].second)
            {
                endAt[i].first++;
                endAt[i].second = arr[i];
            }
        }

        build(1, 1, len);

        MonoStack monostk;
        for (int i = len; i > 0; i--)
        {
            monostk.push(arr[i]);
            startFrom[i] = monostk.size();
        }

        while (qNum--)
        {
            int pos, val;
            cin >> pos >> val;

            int ans = endAt[pos - 1].first;
            int cnt = endAt[pos - 1].second;

            if (val > cnt)
            {
                ans++;
                cnt = val;
            }

            if (pos < len)
            {
                pair<int, int> res = query(1, pos + 1, len, cnt);
                if (res.first != -1)
                    ans += startFrom[res.second];
            }

            cout << ans << endl;
        }
    }
    return 0;
}