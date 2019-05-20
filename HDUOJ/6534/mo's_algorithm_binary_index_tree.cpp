#include <bits/stdc++.h>
using namespace std;

#define SIZE 27010

typedef struct _Query {
    int id, qLeftPt, qRightPt;
} Query;

Query qArr[SIZE];
int arr[SIZE], ans[SIZE], len, qNum, lim;
int posArr[SIZE], ansArr[SIZE];
int dsc[SIZE], dscLen;

int bit[SIZE];

pair<int, int> rangeArr[SIZE];
int dscId[SIZE];

int lowbit(int n) {
    return n & -n;
}

void add(int pos, int val) {
    pos++;
    for (int i = pos; i <= len; i += lowbit(i))
        bit[i] += val;
}

int prefixSum(int pos) {
    int ret = 0; pos++;
    for (int i = pos; i > 0; i -= lowbit(i))
        ret += bit[i];
    return ret;
}

int rangeSum(int qLeftPt, int qRightPt) {
    return prefixSum(qRightPt) - prefixSum(qLeftPt - 1);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
   
    while (cin >> len >> qNum >> lim) {
        memset(bit, 0, sizeof(bit));
        for (int i = 0; i < len; i++) {
            cin >> arr[i];
            dsc[i] = arr[i];
        }

        sort(dsc + 0, dsc + len);
        dscLen = unique(dsc + 0, dsc + len) - dsc;

        for (int i = 0; i < qNum; i++) {
            qArr[i].id = i;
            cin >> qArr[i].qLeftPt >> qArr[i].qRightPt;
            qArr[i].qLeftPt--; qArr[i].qRightPt--;
        }

        // Partition
        int blockSize = sqrt(len);
        for (int i = 0; i < len; i++)
            posArr[i] = i / blockSize;

        sort(qArr + 0, qArr + qNum, [](const Query & fst, const Query & snd) {
            if (posArr[fst.qLeftPt] == posArr[snd.qLeftPt])
                return fst.qRightPt < snd.qRightPt;
            return posArr[fst.qLeftPt] < posArr[snd.qLeftPt];
        });

        // Initialize range
        for (int i = 0; i < len; i++) {
            rangeArr[i].first = lower_bound(dsc + 0, dsc + dscLen, arr[i] - lim) - dsc;
            rangeArr[i].second = lower_bound(dsc + 0, dsc + dscLen, arr[i] + lim + 1) - dsc - 1;
            dscId[i] = lower_bound(dsc + 0, dsc + dscLen, arr[i]) - dsc;
        }
        
        int cntLeftPt = 0, cntRightPt = 0, cntAns = 0;
        add(dscId[0], 1);

        for (int i = 0; i < qNum; i++) {
            while (qArr[i].qLeftPt < cntLeftPt) {
                // Add left
                cntLeftPt--;
                int cntPt = cntLeftPt;
                cntAns += rangeSum(rangeArr[cntPt].first, rangeArr[cntPt].second);
                add(dscId[cntPt], 1);
            }

            while (qArr[i].qRightPt > cntRightPt) {
                // Add right
                cntRightPt++;
                int cntPt = cntRightPt;
                cntAns += rangeSum(rangeArr[cntPt].first, rangeArr[cntPt].second);
                add(dscId[cntPt], 1);
            }

            while (qArr[i].qLeftPt > cntLeftPt) {
                // Delete left
                int cntPt = cntLeftPt;
                add(dscId[cntPt], -1);
                cntAns -= rangeSum(rangeArr[cntPt].first, rangeArr[cntPt].second);
                cntLeftPt++;
            }

            while (qArr[i].qRightPt < cntRightPt) {
                // Delete right
                int cntPt = cntRightPt;
                add(dscId[cntPt], -1);
                cntAns -= rangeSum(rangeArr[cntPt].first, rangeArr[cntPt].second);
                cntRightPt--;
            }

            ans[qArr[i].id] = cntAns;
        }

        for (int i = 0; i < qNum; i++)
            cout << ans[i] << '\n';
    }

    return 0;
}