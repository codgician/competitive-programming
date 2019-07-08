#include <bits/stdc++.h>
using namespace std;

#define SIZE 50010

typedef struct _Node {
    int id, r, l;
} Node;

Node arr[SIZE], tmp[SIZE];

bool cmpSnd(const Node & fst, const Node & snd) {
    if (fst.r != snd.r)
        return fst.r < snd.r;
    if (fst.l != snd.l)
        return fst.l > snd.l;
    return fst.id < snd.id;
}

bool cmpFst(const Node & fst, const Node & snd) {
    if (fst.id != snd.id)
        return fst.id < snd.id;
    return cmpSnd(fst, snd);
}

int dsc[SIZE], pre[SIZE], len;
pair<int, int> bit[SIZE], dp[SIZE];
vector<int> vec;

bool upd(pair<int, int> & ret, const pair<int, int> & val) {
    if (ret.first < val.first || (ret.first == val.first && ret.second > val.second)) {
        ret = val; return true;
    }
    return false;
}

int lowbit(int n) {
    return n & -n;
}

void addMax(int pos, const pair<int, int> & val) {
    pos++;
    for (int i = pos; i <= len; i += lowbit(i))
        upd(bit[i], val);
}

void clear(int pos) {
    pos++;
    for (int i = pos; i <= len; i += lowbit(i))
        bit[i] = make_pair(0, INT_MAX);
}

pair<int, int> prefixMax(int pos) {
    pair<int, int> ret = make_pair(0, INT_MAX); pos++;
    for (int i = pos; i > 0; i -= lowbit(i))
        upd(ret, bit[i]);
    return ret;
}

void divideConquer(int headPt, int tailPt) {
    if (headPt == tailPt)
        return;
    int midPt = (headPt + tailPt) >> 1;
    divideConquer(midPt + 1, tailPt);

    copy(arr + headPt, arr + midPt + 1, tmp + headPt);
    sort(arr + headPt, arr + midPt + 1, cmpSnd);

    int j = tailPt;
    for (int i = midPt; i >= headPt; i--) {
        for (; j > midPt && arr[j].r >= arr[i].r; j--)
            addMax(arr[j].l, make_pair(dp[arr[j].id].first, arr[j].id));
        pair<int, int> ret = prefixMax(arr[i].l); ret.first += 1;
        upd(dp[arr[i].id], ret);
    }

    for (int i = j + 1; i <= tailPt; i++)
        clear(arr[i].l);
    
    copy(tmp + headPt, tmp + midPt + 1, arr + headPt);
    divideConquer(headPt, midPt);
    inplace_merge(arr + headPt, arr + midPt + 1, arr + tailPt + 1, cmpSnd);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    while (cin >> len) {
        fill(bit + 0, bit + len + 1, make_pair(0, INT_MAX));
        fill(dp + 0, dp + len + 1, make_pair(1, INT_MAX));
        int dscPt = 0;
        for (int i = 0; i < len; i++) {
            cin >> arr[i].l; arr[i].id = i;
            dsc[dscPt++] = arr[i].l;
        }
        for (int i = 0; i < len; i++)
            cin >> arr[i].r;
        
        sort(dsc + 0, dsc + dscPt);
        dscPt = unique(dsc + 0, dsc + dscPt) - dsc;
        for (int i = 0; i < len; i++)
            arr[i].l = lower_bound(dsc + 0, dsc + dscPt, arr[i].l) - dsc;

        divideConquer(0, len - 1);

        pair<int, int> ans = dp[0]; int cntPt = 0;
        for (int i = 1; i < len; i++)
            if (upd(ans, dp[i]))
                cntPt = i;

        cout << ans.first << '\n';
        while (cntPt != INT_MAX) {
            cout << cntPt + 1;
            cntPt = dp[cntPt].second;
            cout << (cntPt == INT_MAX ? '\n' : ' ');
        }
    }

    return 0;
}