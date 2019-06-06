#include <bits/stdc++.h>
using namespace std;

#define SIZE 500010
#define VAL_SIZE 1000010

typedef struct _Query {
    int id, qLeftPt, qRightPt;
} Query;

Query qArr[SIZE];

int pre[SIZE], last[VAL_SIZE], ans[SIZE], bit[SIZE];
pair<int, int> arr[SIZE];

int lowbit(int n) {
    return n & -n;
}

void add(int pos, int val) {
    pos += 2;
    for (int i = pos; i < SIZE; i += lowbit(i))
        bit[i] += val;
}

int prefixSum(int pos) {
    int ret = 0; pos += 2;
    for (int i = pos; i > 0; i -= lowbit(i))
        ret += bit[i];
    return ret;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    memset(last, -1, sizeof(last));
    memset(bit, 0, sizeof(bit));
    int len, qNum;
    cin >> len;
    for (int i = 0; i < len; i++) {
        int cnt; cin >> cnt;
        pre[i] = last[cnt];
        last[cnt] = i;
        arr[i] = make_pair(pre[i], i);
    }
    cin >> qNum;
    for (int i = 0; i < qNum; i++) {
        qArr[i].id = i;
        cin >> qArr[i].qLeftPt >> qArr[i].qRightPt;
        qArr[i].qLeftPt--; qArr[i].qRightPt--;
    }

    sort(arr + 0, arr + len);
    sort(qArr + 0, qArr + qNum, [](const Query & fst, const Query & snd) {
        return fst.qLeftPt < snd.qLeftPt;
    });

    int cntPt = 0;
    for (int i = 0; i < qNum; i++) {
        // (-1, l) <= (p, i) <= (l - 1, r)
        while (arr[cntPt].first <= qArr[i].qLeftPt - 1)
            add(arr[cntPt++].second, 1);
        ans[qArr[i].id] += prefixSum(qArr[i].qRightPt) - prefixSum(qArr[i].qLeftPt - 1);
    }
    for (int i = 0; i < qNum; i++)
        cout << ans[i] << '\n';

    return 0;
}