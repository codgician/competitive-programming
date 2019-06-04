#include <bits/stdc++.h>
using namespace std;

#define SIZE 100100

typedef struct _Node {
    int val, id;
    bool operator < (const struct _Node & snd) const {
        return val < snd.val;
    }
} Node;

Node arr[SIZE];

typedef struct _Query {
    int qLeftPt, qRightPt, k;
    int id, cnt;
} Query;

Query qArr[SIZE], bkt[SIZE];
int ans[SIZE], bit[SIZE], len, qNum;

int lowbit(int n) {
    return n & -n;
}

void add(int pos, int val) {
    for (int i = pos; i <= len; i += lowbit(i))
        bit[i] += val;
}

int getPrefixSum(int pos) {
    int ret = 0;
    for (int i = pos; i > 0; i -= lowbit(i))
        ret += bit[i];
    return ret;
}

void divideConquer(int headPt, int tailPt, int leftPt, int rightPt) {
    if (leftPt == rightPt) {
        for (int i = headPt; i <= tailPt; i++)
            ans[qArr[i].id] = rightPt;
        return;
    }
    int midPt = (leftPt + rightPt) >> 1;
    // First element that is not smaller than leftPt
    int pos = lower_bound(arr + 0, arr + len, Node{leftPt, -1}) - arr;
    // Update BIT
    for (int i = pos; i < len && arr[i].val <= midPt; i++)
        add(arr[i].id + 1, 1);
    // Calculate cnt
    for (int i = headPt; i <= tailPt; i++)
        qArr[i].cnt = getPrefixSum(qArr[i].qRightPt + 1) - getPrefixSum(qArr[i].qLeftPt);
    // Restore BIT
    for (int i = pos; i < len && arr[i].val <= midPt; i++)
        add(arr[i].id + 1, -1);
    // Divide And Conquer
    int bktHeadPt = headPt, bktTailPt = tailPt;
    for (int i = headPt; i <= tailPt; i++) {
        if (qArr[i].cnt >= qArr[i].k) {
            bkt[bktHeadPt++] = qArr[i];
        } else {
            qArr[i].k -= qArr[i].cnt;
            bkt[bktTailPt--] = qArr[i];
        }
    }
    for (int i = headPt; i <= tailPt; i++)
        qArr[i] = bkt[i];
    if (bktHeadPt != headPt)
        divideConquer(headPt, bktHeadPt - 1, leftPt, midPt);
    if (bktTailPt != tailPt)
        divideConquer(bktTailPt + 1, tailPt, midPt + 1, rightPt);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    while (cin >> len >> qNum) {
        memset(bit, 0, sizeof(bit));
        int minVal = INT_MAX, maxVal = INT_MIN;
        for (int i = 0; i < len; i++) {
            cin >> arr[i].val;
            minVal = min(minVal, arr[i].val);
            maxVal = max(maxVal, arr[i].val);
            arr[i].id = i;
        }
        sort(arr + 0, arr + len);
        for (int i = 0; i < qNum; i++) {
            cin >> qArr[i].qLeftPt >> qArr[i].qRightPt >> qArr[i].k;
            qArr[i].qLeftPt--; qArr[i].qRightPt--;
            qArr[i].id = i; qArr[i].cnt = 0;
        }
        divideConquer(0, qNum - 1, minVal, maxVal);
        for (int i = 0; i < qNum; i++)
            cout << ans[i] << '\n';
    }
    return 0;
}