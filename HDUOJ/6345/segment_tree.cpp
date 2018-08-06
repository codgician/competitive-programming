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

typedef struct _SegNode
{
    int leftPt, rightPt;
    char minChar;
    int minNum;
} SegNode;

SegNode segTree[SIZE << 2];
char arr[SIZE];

void pushUp(int segPt)
{
    if (segTree[LEFT_SON].minChar < segTree[RIGHT_SON].minChar)
    {
        segTree[segPt].minChar = segTree[LEFT_SON].minChar;
        segTree[segPt].minNum = segTree[LEFT_SON].minNum;
    }
    else if (segTree[LEFT_SON].minChar > segTree[RIGHT_SON].minChar)
    {
        segTree[segPt].minChar = segTree[RIGHT_SON].minChar;
        segTree[segPt].minNum = segTree[RIGHT_SON].minNum;
    }
    else
    {
        segTree[segPt].minChar = segTree[LEFT_SON].minChar;
        segTree[segPt].minNum = segTree[LEFT_SON].minNum + segTree[RIGHT_SON].minNum;
    }

}

void build(int segPt, int leftPt, int rightPt)
{
    segTree[segPt].leftPt = leftPt;
    segTree[segPt].rightPt = rightPt;

    if (leftPt == rightPt)
    {
        segTree[segPt].minChar = arr[leftPt];
        segTree[segPt].minNum = 1;
        return;
    }

    int midPt = (leftPt + rightPt) >> 1;
    build(LEFT_SON, leftPt, midPt);
    build(RIGHT_SON, midPt + 1, rightPt);
    pushUp(segPt);
}

pair<char, int> query(int segPt, int qLeftPt, int qRightPt)
{
    if (segTree[segPt].leftPt >= qLeftPt && segTree[segPt].rightPt <= qRightPt)
    {
        return make_pair(segTree[segPt].minChar, segTree[segPt].minNum);
    }

    pair<char, int> ans = make_pair('Z', 0);
    int midPt = (segTree[segPt].leftPt + segTree[segPt].rightPt) >> 1;
    if (qLeftPt <= midPt)
    {
        pair<char, int> cnt = query(LEFT_SON, qLeftPt, qRightPt);
        if (cnt.first < ans.first)
            ans = cnt;
        else if (cnt.first == ans.first)
            ans.second += cnt.second;
    }
    if (qRightPt > midPt)
    {
        pair<char, int> cnt = query(RIGHT_SON, qLeftPt, qRightPt);
        if (cnt.first < ans.first)
            ans = cnt;
        else if (cnt.first == ans.first)
            ans.second += cnt.second;
    }
    return ans;
}

int main()
{
    int caseNum;
    scanf("%d", &caseNum);
    for (int t = 1; t <= caseNum; t++)
    {
        int len, qNum;
        scanf("%d%d", &len, &qNum);
        scanf("%s", arr + 1);

        build(1, 1, len);

        printf("Case #%d:\n", t);
        while (qNum--)
        {
            int qLeftPt, qRightPt;
            scanf("%d%d", &qLeftPt, &qRightPt);
            printf("%d\n", query(1, qLeftPt, qRightPt).second);
        }
    }
    return 0;
}