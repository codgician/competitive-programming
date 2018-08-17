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

#define SIZE 100100
#define LEFT_SON (segPt << 1)
#define RIGHT_SON (segPt << 1 | 1)

typedef struct _SegNode
{
    int leftPt, rightPt;
    bool existArr[2][2];
    long long int sumArr[2][2];
} SegNode;

SegNode segTree[SIZE << 2];
long long int arr[SIZE];

SegNode mergeNode(const SegNode & fst, const SegNode & snd)
{
    SegNode ans;

    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            ans.existArr[i][j] = false;
            ans.sumArr[i][j] = LLONG_MIN;

            if (fst.existArr[i][j])
            {
                ans.existArr[i][j] = true;
                ans.sumArr[i][j] = max(ans.sumArr[i][j], fst.sumArr[i][j]);
            }

            if (snd.existArr[i][j])
            {
                ans.existArr[i][j] = true;
                ans.sumArr[i][j] = max(ans.sumArr[i][j], snd.sumArr[i][j]);
            }

            for (int k = 0; k < 2; k++)
            {
                if (fst.existArr[i][k] && snd.existArr[k ^ 1][j])
                {
                    ans.existArr[i][j] = true;
                    ans.sumArr[i][j] = max(ans.sumArr[i][j], fst.sumArr[i][k] + snd.sumArr[k ^ 1][j]);
                }
            }
        }
    }

    return ans;
}

void pushUp(int segPt)
{
    int leftPt = segTree[segPt].leftPt;
    int rightPt = segTree[segPt].rightPt;
    segTree[segPt] = mergeNode(segTree[LEFT_SON], segTree[RIGHT_SON]);
    segTree[segPt].leftPt = leftPt;
    segTree[segPt].rightPt = rightPt;
}

void build(int segPt, int leftPt, int rightPt)
{
    segTree[segPt].leftPt = leftPt;
    segTree[segPt].rightPt = rightPt;

    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            segTree[segPt].existArr[i][j] = false;
            segTree[segPt].sumArr[i][j] = LLONG_MIN;
        }
    }

    if (leftPt == rightPt)
    {
        segTree[segPt].existArr[leftPt & 1][leftPt & 1] = true;
        segTree[segPt].sumArr[leftPt & 1][leftPt & 1] = arr[leftPt];
        return;
    }

    int midPt = (leftPt + rightPt) >> 1;
    build(LEFT_SON, leftPt, midPt);
    build(RIGHT_SON, midPt + 1, rightPt);
    pushUp(segPt);
}

void update(int segPt, int cntPt, long long int val)
{
    if (segTree[segPt].leftPt == segTree[segPt].rightPt)
    {
        segTree[segPt].sumArr[segTree[segPt].leftPt & 1][segTree[segPt].leftPt & 1] = val;
        return;
    }

    int midPt = (segTree[segPt].leftPt + segTree[segPt].rightPt) >> 1;
    if (cntPt <= midPt)
        update(LEFT_SON, cntPt, val);
    else
        update(RIGHT_SON, cntPt, val);
    pushUp(segPt);
}

SegNode query(int segPt, int qLeftPt, int qRightPt)
{
    if (segTree[segPt].leftPt >= qLeftPt && segTree[segPt].rightPt <= qRightPt)
    {
        return segTree[segPt];
    }

    SegNode ans;
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            ans.existArr[i][j] = false;
            ans.sumArr[i][j] = LLONG_MIN;
        }
    }

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

        build(1, 1, len);

        while (qNum--)
        {
            bool opr;
            cin >> opr;
            if (opr == 0)
            {
                // query
                int qLeftPt, qRightPt;
                cin >> qLeftPt >> qRightPt;
                SegNode res = query(1, qLeftPt, qRightPt);
                
                long long int ans = LLONG_MIN;
                for (int i = 0; i < 2; i++)
                {
                    for (int j = 0; j < 2; j++)
                    {
                        if (res.existArr[i][j])
                        {
                            ans = max(ans, res.sumArr[i][j]);
                        }
                    }
                }

                cout << ans << endl;
            }
            else
            {
                // update
                int pos;
                long long int val;
                cin >> pos >> val;
                update(1, pos, val);
            }
        }
    }
    return 0;
}