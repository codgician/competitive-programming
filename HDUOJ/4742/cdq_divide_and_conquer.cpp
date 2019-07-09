#include <bits/stdc++.h>
using namespace std;

#define SIZE 100010

const int mod = 1 << 30;

typedef struct _Node {
    int x, y, z;
} Node;

Node arr[SIZE], tmp[SIZE];

pair<int, int> dp[SIZE], bit[SIZE];
int dsc[SIZE], len;

void upd(pair<int, int> & ret, const pair<int, int> & val) {
    if (ret.first < val.first)
        ret = val;
    else if (ret.first == val.first)
        ret.second += val.second, ret.second -= (ret.second >= mod ? mod : 0);
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
        bit[i] = make_pair(0, 0);
}

pair<int, int> prefixMax(int pos) {
    pair<int, int> ret = make_pair(0, 0); pos++;
    for (int i = pos; i > 0; i -= lowbit(i))
        upd(ret, bit[i]);
    return ret;
}

bool cmpSnd(const Node & fst, const Node & snd) {
    if (fst.y != snd.y)
        return fst.y < snd.y;
    return fst.z < snd.z;
}

bool cmpFst(const Node & fst, const Node & snd) {
    if (fst.x != snd.x)
        return fst.x < snd.x;
    return cmpSnd(fst, snd);
}

void divideConquer(int headPt, int tailPt) {
    if (headPt == tailPt)
        return;

    int midPt = (headPt + tailPt) >> 1;
    divideConquer(headPt, midPt);
    
    copy(arr + midPt + 1, arr + tailPt + 1, tmp + midPt + 1);
    sort(arr + midPt + 1, arr + tailPt + 1, cmpSnd);

    int j = headPt;
    for (int i = midPt + 1; i <= tailPt; i++) {
        for (; j <= midPt && arr[j].y <= arr[i].y; j++)
            addMax(arr[j].z, dp[arr[j].x]);
        
        pair<int, int> ret = prefixMax(arr[i].z); ret.first++;
        upd(dp[arr[i].x], ret);
    }

    for (int i = headPt; i <= j; i++)
        clear(arr[i].z);

    copy(tmp + midPt + 1, tmp + tailPt + 1, arr + midPt + 1);
    divideConquer(midPt + 1, tailPt);
    inplace_merge(arr + headPt, arr + midPt + 1, arr + tailPt + 1, cmpSnd);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int caseNum; cin >> caseNum;
    while (caseNum--) {
        cin >> len;
        fill(bit + 0, bit + len, make_pair(0, 0));
        for (int i = 0; i < len; i++) {
            cin >> arr[i].x >> arr[i].y >> arr[i].z;
            dsc[i] = arr[i].z;
        }

        sort(arr + 0, arr + len, cmpFst);
        sort(dsc + 0, dsc + len);
        int dscLen = unique(dsc + 0, dsc + len) - dsc;

        for (int i = 0; i < len; i++) {
            arr[i].z = lower_bound(dsc + 0, dsc + dscLen, arr[i].z) - dsc;
            arr[i].x = i; dp[i] = make_pair(1, 1);
        }

        divideConquer(0, len - 1);

        pair<int, int> ans = make_pair(0, 0);
        for (int i = 0; i < len; i++)
            upd(ans, dp[i]);
        cout << ans.first << " " << ans.second << endl; 
    }

    return 0;
}