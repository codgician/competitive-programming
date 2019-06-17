#include <bits/stdc++.h>
using namespace std;

#define SIZE 500010

/* Binary Indexed Tree */

int bit[SIZE];

int lowbit(int n) {
    return n & -n;
}

void add(int pos, int val) {
    for (int i = pos; i < SIZE; i += lowbit(i))
        bit[i] += val;
}

int queryByRank(int rnk) {
    int ans = 0, sum = 0;
    for (int i = log2(SIZE); i >= 0; i--) {
        if (ans + (1 << i) < SIZE && sum + bit[ans + (1 << i)] < rnk) {
            ans += 1 << i;
            sum += bit[ans];
        }
    }
    return ans + 1;
}

vector<pair<int, int> > vec;
pair<long long int, int> qArr[SIZE];
int num[SIZE], ans[SIZE];
long long int pfx[SIZE];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    memset(num, 0, sizeof(num));
    int befNum, cityNum, qNum;
    cin >> befNum >> cityNum >> qNum;
    for (int i = 0; i < befNum; i++) {
        int cnt; cin >> cnt;
        num[cnt]++;
    }

    for (int i = 1; i <= cityNum; i++)
        vec.push_back(make_pair(num[i], i));
    sort(vec.begin(), vec.end());

    pfx[0] = 0;
    for (int i = 0; i < (int)vec.size() - 1; i++) {
        pfx[i] += 1ll * (vec[i + 1].first - vec[i].first) * (i + 1);
        pfx[i + 1] = pfx[i];
    }

    for (int i = 0; i < qNum; i++) {
        cin >> qArr[i].first;
        qArr[i].first -= befNum;
        qArr[i].second = i;
    }
    sort(qArr + 0, qArr + qNum);

    int cntPt = 0;
    for (int i = 0; i < qNum; i++) {
        int pos = lower_bound(pfx + 0, pfx + cityNum - 1, qArr[i].first) - pfx;
        if (pos > 0)
            qArr[i].first -= pfx[pos - 1];
        while (cntPt < (int)vec.size() && cntPt < pos + 1)
            add(vec[cntPt++].second, 1);
        
        int rnk = (qArr[i].first - 1) % (pos + 1) + 1;
        ans[qArr[i].second] = queryByRank(rnk);
    }

    for (int i = 0; i < qNum; i++)
        cout << ans[i] << '\n';
    return 0;
}