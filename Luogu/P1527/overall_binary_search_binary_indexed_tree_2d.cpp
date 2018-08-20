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

#define MAT_SIZE 510
#define QUE_SIZE 60010

typedef struct _Node
{
    int val;
    pair<int, int> id;

    bool operator < (const struct _Node & snd) const
    {
        return val < snd.val;
    }
} Node;

Node arr[MAT_SIZE * MAT_SIZE];

typedef struct _Query
{
    pair<int, int> qUpperLeftPt, qLowerRightPt;
    int k, id, cntNum;
} Query;

Query qArr[QUE_SIZE], bucket[QUE_SIZE];

int ans[QUE_SIZE];

int bitArr[MAT_SIZE][MAT_SIZE];

int matSize, len, qNum;

int getLowbit(int n)
{
    return n & -n;
}

void add(const pair<int, int> & pos, int val)
{
    for (int i = pos.first; i <= matSize; i += getLowbit(i))
    {
        for (int j = pos.second; j <= matSize; j += getLowbit(j))
        {
            bitArr[i][j] += val;
        }
    }
}

int getSum(const pair<int, int> & pos)
{
    int ans = 0;
    for (int i = pos.first; i > 0; i -= getLowbit(i))
    {
        for (int j = pos.second; j > 0; j -= getLowbit(j))
        {
            ans += bitArr[i][j];
        }
    }
    return ans;
}

void rangeAdd(const pair<int, int> & upperLeftPt, const pair<int, int> & lowerRightPt, int val)
{
    add(upperLeftPt, val);
    add(make_pair(lowerRightPt.first + 1, lowerRightPt.second + 1), val);

    add(make_pair(upperLeftPt.first, lowerRightPt.second + 1), -val);
    add(make_pair(lowerRightPt.first + 1, upperLeftPt.second), -val);
}

int getRangeSum(const pair<int, int> & upperLeftPt, const pair<int, int> & lowerRightPt)
{
    int ans = getSum(lowerRightPt);

    if (upperLeftPt.first > 0)
    {
        ans -= getSum(make_pair(upperLeftPt.first - 1, lowerRightPt.second));
    }
    if (upperLeftPt.second > 0)
    {
        ans -= getSum(make_pair(lowerRightPt.first, upperLeftPt.second - 1));
    }
    if (upperLeftPt.first > 0 && upperLeftPt.second > 0)
    {
        ans += getSum(make_pair(upperLeftPt.first - 1, upperLeftPt.second - 1));
    }

    return ans;
}

void divideConquer(int headPt, int tailPt, int leftPt, int rightPt)
{
    if (leftPt == rightPt)
    {
        for (int i = headPt; i <= tailPt; i++)
        {
            ans[qArr[i].id] = rightPt;
        }
        return;
    }

    int midPt = (leftPt + rightPt) >> 1;

    // First element that is not smaller than leftPt
    int pos = lower_bound(arr + 0, arr + len, Node{leftPt}) - arr;

    // Update BIT
    for (int i = pos; i < len && arr[i].val <= midPt; i++)
    {
        add(make_pair(arr[i].id.first + 1, arr[i].id.second + 1), 1);
    }

    for (int i = headPt; i <= tailPt; i++)
    {
        qArr[i].cntNum = getRangeSum(make_pair(qArr[i].qUpperLeftPt.first + 1, qArr[i].qUpperLeftPt.second + 1), 
            make_pair(qArr[i].qLowerRightPt.first + 1, qArr[i].qLowerRightPt.second + 1));
    }

    // Restore BIT
    for (int i = pos; i < len && arr[i].val <= midPt; i++)
    {
        add(make_pair(arr[i].id.first + 1, arr[i].id.second + 1), -1);
    }

    int bktHeadPt = headPt, bktTailPt = tailPt;
    for (int i = headPt; i <= tailPt; i++)
    {
        if (qArr[i].cntNum >= qArr[i].k)
        {
            bucket[bktHeadPt++] = qArr[i];
        }
        else
        {
            qArr[i].k -= qArr[i].cntNum;
            bucket[bktTailPt--] = qArr[i];
        }
    }

    for (int i = headPt; i <= tailPt; i++)
    {
        qArr[i] = bucket[i];
    }

    if (bktHeadPt != headPt)
        divideConquer(headPt, bktHeadPt - 1, leftPt, midPt);
    if (bktTailPt != tailPt)
        divideConquer(bktTailPt + 1, tailPt, midPt + 1, rightPt);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> matSize >> qNum;
    
    memset(bitArr, 0, sizeof(bitArr));
    int minVal = INT_MAX, maxVal = INT_MIN;
    len = 0;
    for (int i = 0; i < matSize; i++)
    {
        for (int j = 0; j < matSize; j++)
        {
            cin >> arr[len].val;
            minVal = min(minVal, arr[len].val);
            maxVal = max(maxVal, arr[len].val);
            arr[len].id = make_pair(i, j);
            len++;
        }
    }

    sort(arr + 0, arr + len);

    for (int i = 0; i < qNum; i++)
    {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2 >> qArr[i].k;
        qArr[i].qUpperLeftPt = make_pair(x1 - 1, y1 - 1);
        qArr[i].qLowerRightPt = make_pair(x2 - 1, y2 - 1);
        qArr[i].id = i;
        qArr[i].cntNum = 0;
    }

    divideConquer(0, qNum - 1, minVal, maxVal);

    for (int i = 0; i < qNum; i++)
    {
        cout << ans[i] << endl;
    }
    
    return 0;
}