#include <bits/stdc++.h>
using namespace std;

#define SIZE 50010
#define QUE_SIZE 10010
#define OPR_SIZE 70010

// If k == 0: modify;
// qLeftPt = pos, qRightPt = val, cnt = type (-1: delete | 1: add)
typedef struct _Opr {
    int qLeftPt, qRightPt, k;   // pos, val, 0
    int qId, cnt;            // -1, type
} Opr;

Opr oprArr[OPR_SIZE], fstBkt[OPR_SIZE], sndBkt[OPR_SIZE];
int arr[SIZE], ans[QUE_SIZE], bit[SIZE], len;

int lowbit(int n) {
    return n & -n;
}

void add(int pos, int val) {
    for (int i = pos; i <= len; i += lowbit(i))
        bit[i] += val;
}

int prefixSum(int pos) {
    int ret = 0;
    for (int i = pos; i > 0; i -= lowbit(i))
        ret += bit[i];
    return ret;
}

void divideConquer(int headPt, int tailPt, int leftPt, int rightPt) {
    if (leftPt == rightPt) {
        for (int i = headPt; i <= tailPt; i++) {
            if (oprArr[i].k == 0)   // Skip modifications
                continue;
            ans[oprArr[i].qId] = rightPt;
        }
        return;
    }

    int midPt = (leftPt + rightPt) >> 1;

    // Update BIT && Calculate cnt
    for (int i = headPt; i <= tailPt; i++) {
        if (oprArr[i].k > 0)    // query
            oprArr[i].cnt = prefixSum(oprArr[i].qRightPt + 1) - prefixSum(oprArr[i].qLeftPt);
        else if (oprArr[i].qRightPt <= midPt)   // modify
            add(oprArr[i].qLeftPt + 1, oprArr[i].cnt);
    }

    // Restore BIT
    for (int i = headPt; i <= tailPt; i++)
        if (oprArr[i].k == 0 && oprArr[i].qRightPt <= midPt)
            add(oprArr[i].qLeftPt + 1, -oprArr[i].cnt);

    // Divide And Conquer
    int fstPt = 0, sndPt = 0;
    for (int i = headPt; i <= tailPt; i++) {
        if (oprArr[i].k > 0) {
            // query
            if (oprArr[i].k <= oprArr[i].cnt) {
                fstBkt[fstPt++] = oprArr[i];
            } else {
                oprArr[i].k -= oprArr[i].cnt;
                sndBkt[sndPt++] = oprArr[i];
            }
        } else {
            // modify
            if (oprArr[i].qRightPt <= midPt)
                fstBkt[fstPt++] = oprArr[i];
            else
                sndBkt[sndPt++] = oprArr[i];
        }
    }
    for (int i = 0; i < fstPt; i++)
        oprArr[headPt + i] = fstBkt[i];
    for (int i = 0; i < sndPt; i++)
        oprArr[headPt + fstPt + i] = sndBkt[i];
    if (fstPt > 0)
        divideConquer(headPt, headPt + fstPt - 1, leftPt, midPt);
    if (sndPt > 0)
        divideConquer(headPt + fstPt, tailPt, midPt + 1, rightPt);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int caseNum;
    cin >> caseNum;
    while (caseNum--) {
        memset(bit, 0, sizeof(bit));
        int qNum, oprPt = 0, qPt = 0, minVal = INT_MAX, maxVal = 0;
        cin >> len >> qNum;
        for (int i = 0; i < len; i++) {
            // treat original array as insertions
            cin >> arr[i];
            minVal = min(minVal, arr[i]);
            maxVal = max(maxVal, arr[i]);
            oprArr[oprPt++] = {i, arr[i], 0, -1, 1};
        }
        for (int i = 0; i < qNum; i++) {
            char opr; cin >> opr;
            if (opr == 'Q') {
                int qLeftPt, qRightPt, k;
                cin >> qLeftPt >> qRightPt >> k;
                qLeftPt--, qRightPt--;
                oprArr[oprPt++] = {qLeftPt, qRightPt, k, qPt++, 0};
            } else if (opr == 'C') {
                int pos, val;
                cin >> pos >> val;
                pos--;
                // delete
                oprArr[oprPt++] = {pos, arr[pos], 0, -1, -1};
                // insert
                oprArr[oprPt++] = {pos, val, 0, -1, 1};
                arr[pos] = val;
                minVal = min(minVal, val);
                maxVal = max(maxVal, val);
            }
        }
        divideConquer(0, oprPt - 1, minVal, maxVal);
        for (int i = 0; i < qPt; i++)
            cout << ans[i] << endl;
    }
    return 0;
}