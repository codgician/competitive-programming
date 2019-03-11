#include <bits/stdc++.h>
using namespace std;

#define SIZE 1000010

typedef struct _Query {
    int id, qLeftPt, qRightPt;
    bool operator < (const struct _Query & snd) const {
        if (qLeftPt != snd.qLeftPt)
            return qLeftPt > snd.qLeftPt;
        return qRightPt > snd.qRightPt;
    }
} Query;

Query qArr[SIZE];
int arr[SIZE], pos[SIZE], len, qNum;
long long int bit1[SIZE], bit2[SIZE], ans[SIZE];
pair<int, int> dsc[SIZE];

int lowbit(int x) {
    return x & -x;
}

void add(long long int * bitArr, int pos, long long int val) {
    pos++;
    for (int i = pos; i <= len; i += lowbit(i)) {
        bitArr[i] += val;
    }
}

long long int prefixSum(long long int * bitArr, int pos) {
    pos++;
    long long int ret = 0;
    for (int i = pos; i > 0; i -= lowbit(i)) {
        ret += bitArr[i];
    }
    return ret;
}

long long int rangeSum(long long int * bitArr, int qLeftPt, int qRightPt) {
    return prefixSum(bitArr, qRightPt) - prefixSum(bitArr, qLeftPt - 1);
}

void solve(int dir) {
    sort(qArr + 0, qArr + qNum);
    memset(bit1, 0, sizeof(bit1));
    memset(bit2, 0, sizeof(bit2));

    stack<pair<int, int> > mstk;
    for (int i = 0; i < len; i++) {
        while (!mstk.empty() && mstk.top().first < arr[i]) {
            mstk.pop();
        }
        if (mstk.empty()) {
            pos[i] = -1;
        } else {
            pos[i] = mstk.top().second;
        }
        dsc[i] = make_pair(pos[i], i);
        mstk.push(make_pair(arr[i], i));
    }
    sort(dsc + 0, dsc + len, greater<pair<int, int> >());
    
    int cntPt = -1, dscPt = 0;
    for (int i = 0; i < qNum; i++) {
        int qLen = qArr[i].qRightPt - qArr[i].qLeftPt + 1;
        if (cntPt != qArr[i].qLeftPt) {
            while (dscPt < len && dsc[dscPt].first + 1 >= qArr[i].qLeftPt) {
                if (dir == 0) {
                    add(bit1, dsc[dscPt].second, dsc[dscPt].first + 1);
                } else {
                    add(bit1, dsc[dscPt].second, len - 1 - (dsc[dscPt].first + 1));
                }
                add(bit2, dsc[dscPt].second, 1);
                dscPt++;
            }
            cntPt = qArr[i].qLeftPt;
        }
        long long int cnt = rangeSum(bit1, qArr[i].qLeftPt, qArr[i].qRightPt), baseNum = qLen - rangeSum(bit2, qArr[i].qLeftPt, qArr[i].qRightPt);
        if (dir == 0) {
            cnt += baseNum * qArr[i].qLeftPt;
        } else {
            cnt += baseNum * (len - 1 - qArr[i].qLeftPt);
        }
        ans[qArr[i].id] += ((dir << 1) - 1) * cnt;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    cin >> len >> qNum;
    for (int i = 0; i < len; i++) {
        cin >> arr[i];
    }

    for (int i = 0; i < qNum; i++) {
        cin >> qArr[i].qLeftPt;
        qArr[i].qLeftPt--;
        qArr[i].id = i;
    }
    for (int i = 0; i < qNum; i++) {
        cin >> qArr[i].qRightPt;
        qArr[i].qRightPt--;
        ans[qArr[i].id] = qArr[i].qRightPt - qArr[i].qLeftPt + 1;
    }

    solve(0);
    reverse(arr + 0, arr + len);
    for (int i = 0; i < qNum; i++) {
        int bak = qArr[i].qLeftPt;
        qArr[i].qLeftPt = len - qArr[i].qRightPt - 1;
        qArr[i].qRightPt = len - bak - 1;
    }
    solve(1);

    for (int i = 0; i < qNum; i++) {
        cout << ans[i] << " ";
    }

    return 0;
}