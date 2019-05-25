#include <bits/stdc++.h>
using namespace std;

#define SIZE 5000010

typedef struct _Query {
    int qLeftPt, qRightPt;
    int val, id;
} Query;

Query qArr[SIZE];
int arr[SIZE], pfxNum[SIZE];
int bit[SIZE], len;

vector<pair<int, int> > vec;

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

int rangeSum(int qLeftPt, int qRightPt) {
    return prefixSum(qRightPt) - prefixSum(qLeftPt - 1);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> len;
    pfxNum[0] = 0;
    for (int i = 1; i <= len; i++) {
        cin >> arr[i];
        pfxNum[i] = pfxNum[i - 1] + (arr[i] == i);
        vec.push_back(make_pair(arr[i] + i, i));
    }

    for (int i = 1; i <= len; i++) {
        qArr[i] = {i, arr[i], i + arr[i], i};
        if (qArr[i].qLeftPt > qArr[i].qRightPt)
            swap(qArr[i].qLeftPt, qArr[i].qRightPt);
    }

    sort(vec.begin(), vec.end());
    sort(qArr + 1, qArr + len + 1, [](Query & fst, Query & snd) {
        return fst.val < snd.val;
    });

    int prev = 0, pStartPt = -1, pEndPt = -1, ans = 0;
    for (int i = 1; i <= len; i++) {
        if (qArr[i].val != prev) {
            // delete prev
            if (pStartPt != -1) {
                for (int j = pStartPt; j <= pEndPt; j++)
                    add(vec[j].second, -1);
            }

            // add current
            pStartPt = pEndPt + 1;
            prev = vec[pStartPt].first;
            int cntPt = pStartPt;
            while (cntPt < (int)vec.size() && vec[cntPt].first == prev) {
                add(vec[cntPt].second, 1);
                cntPt++;
            }
            pEndPt = cntPt - 1;
        }

        ans = max(ans, rangeSum(qArr[i].qLeftPt, qArr[i].qRightPt) + pfxNum[len] - (pfxNum[qArr[i].qRightPt] - pfxNum[qArr[i].qLeftPt - 1]));
    }

    cout << ans << '\n';
    return 0;
}