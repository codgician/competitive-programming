#include <bits/stdc++.h>
using namespace std;

#define SIZE 200020
#define OFFSET 100002

#define LEFT_SON (segPt << 1)
#define RIGHT_SON (segPt << 1 | 1)

typedef struct _SegNode {
    int leftPt, rightPt;
    int sum;
    int mulLazy, updLazy;
} SegNode;
SegNode segTree[SIZE << 2];

void pushUp(int segPt) {
    segTree[segPt].sum = segTree[LEFT_SON].sum + segTree[RIGHT_SON].sum;
}

void pushDown(int segPt) {
    if (segTree[segPt].updLazy != 0) {
        segTree[LEFT_SON].sum = segTree[segPt].updLazy * (segTree[LEFT_SON].rightPt - segTree[LEFT_SON].leftPt + 1);
        segTree[RIGHT_SON].sum = segTree[segPt].updLazy * (segTree[RIGHT_SON].rightPt - segTree[RIGHT_SON].leftPt + 1);

        segTree[LEFT_SON].updLazy = segTree[segPt].updLazy;
        segTree[LEFT_SON].mulLazy = 1;
        segTree[RIGHT_SON].updLazy = segTree[segPt].updLazy;
        segTree[RIGHT_SON].mulLazy = 1;

        segTree[segPt].updLazy = 0;
    }

    if (segTree[segPt].mulLazy != 1) {
        segTree[LEFT_SON].sum *= segTree[segPt].mulLazy;
        segTree[RIGHT_SON].sum *= segTree[segPt].mulLazy;

        segTree[LEFT_SON].mulLazy *= segTree[segPt].mulLazy;
        segTree[RIGHT_SON].mulLazy *= segTree[segPt].mulLazy;

        segTree[segPt].mulLazy = 1;
    }
}

void build(int segPt, int leftPt, int rightPt) {
    segTree[segPt].leftPt = leftPt;
    segTree[segPt].rightPt = rightPt;
    segTree[segPt].updLazy = 0;
    segTree[segPt].mulLazy = 1;
    if (leftPt == rightPt) {
        segTree[segPt].sum = 1;
        return;
    }
    int midPt = (leftPt + rightPt) >> 1;
    build(LEFT_SON, leftPt, midPt);
    build(RIGHT_SON, midPt + 1, rightPt);
    pushUp(segPt);
}

void rangeUpdate(int segPt, int qLeftPt, int qRightPt, int val) {
    if (segTree[segPt].leftPt >= qLeftPt && segTree[segPt].rightPt <= qRightPt) {
        segTree[segPt].sum = val * (segTree[segPt].rightPt - segTree[segPt].leftPt + 1);
        segTree[segPt].updLazy = val;
        segTree[segPt].mulLazy = 1;
        return;
    }
    pushDown(segPt);
    int midPt = (segTree[segPt].leftPt + segTree[segPt].rightPt) >> 1;
    if (qLeftPt <= midPt)
        rangeUpdate(LEFT_SON, qLeftPt, qRightPt, val);
    if (qRightPt > midPt)
        rangeUpdate(RIGHT_SON, qLeftPt, qRightPt, val);
    pushUp(segPt);
}

void rangeMultiply(int segPt, int qLeftPt, int qRightPt, int val) {
    if (segTree[segPt].leftPt >= qLeftPt && segTree[segPt].rightPt <= qRightPt) {
        segTree[segPt].sum *= val;
        segTree[segPt].mulLazy *= val;
        return;
    }
    pushDown(segPt);
    int midPt = (segTree[segPt].leftPt + segTree[segPt].rightPt) >> 1;
    if (qLeftPt <= midPt)
        rangeMultiply(LEFT_SON, qLeftPt, qRightPt, val);
    if (qRightPt > midPt)
        rangeMultiply(RIGHT_SON, qLeftPt, qRightPt, val);
    pushUp(segPt);
}

int querySum(int segPt, int qLeftPt, int qRightPt) {
    if (segTree[segPt].leftPt >= qLeftPt && segTree[segPt].rightPt <= qRightPt) {
        return segTree[segPt].sum;
    }
    pushDown(segPt);
    int ans = 0;
    int midPt = (segTree[segPt].leftPt + segTree[segPt].rightPt) >> 1;
    if (qLeftPt <= midPt)
        ans += querySum(LEFT_SON, qLeftPt, qRightPt);
    if (qRightPt > midPt)
        ans += querySum(RIGHT_SON, qLeftPt, qRightPt);
    return ans;
}

int arr[SIZE];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int len, qNum;
    cin >> len >> qNum;
    for (int i = 1; i <= len; i++)
        cin >> arr[i];
    build(1, 1, OFFSET << 1);

    while (qNum--) {
        char op; int lim;
        cin >> op >> lim;
        if (op == '>') {
            if (lim >= 0) {
                rangeUpdate(1, OFFSET + lim + 1, OFFSET << 1, -1);
                rangeUpdate(1, 1, OFFSET - lim - 1, 1);
            } else {
                rangeUpdate(1, OFFSET - lim, OFFSET << 1, -1);
                rangeUpdate(1, 1, OFFSET + lim, 1);  
                rangeMultiply(1, OFFSET + lim + 1, OFFSET - lim - 1, -1);
            }
        } else {
            if (lim <= 0) {
                rangeUpdate(1, OFFSET - lim + 1, OFFSET << 1, 1);
                rangeUpdate(1, 1, OFFSET + lim - 1, -1);
            } else {
                rangeUpdate(1, OFFSET + lim, OFFSET << 1, 1);
                rangeUpdate(1, 1, OFFSET - lim, -1);
                rangeMultiply(1, OFFSET - lim + 1, OFFSET + lim - 1, -1);
            }
        }
    }

    for (int i = 1; i <= len; i++)
        cout << querySum(1, OFFSET + arr[i], OFFSET + arr[i]) * arr[i] << (i == len ? '\n' : ' ');

    return 0;
}