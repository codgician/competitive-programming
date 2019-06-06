#include <iostream>
#include <algorithm>
#include <cstring>
#include <set>
using namespace std;

#define SIZE 100010

typedef struct _Query {
    int type;   // 0: Query+, 1: Query-, 2: Modify
    int x, y, val;

    bool operator < (const _Query & snd) const {
        if (x != snd.x)
            return x < snd.x;
        if (y != snd.y)
            return y < snd.y;
        return type < snd.type;
    }
} Query;

Query qArr[SIZE << 3]; 

set<int> st[SIZE];

int arr[SIZE], pre[SIZE], last[SIZE];
long long int bit[SIZE], ans[SIZE];

int lowbit(int n) { 
    return n & -n;
}

void add(int pos, int val) {
    pos += 2;
    for (int i = pos; i < SIZE; i += lowbit(i))
        bit[i] += val;
}

long long int prefixSum(int pos) {
    long long int ret = 0; pos += 2;
    for (int i = pos; i > 0; i -= lowbit(i))
        ret += bit[i];
    return ret;
}

void divideConquer(int headPt, int tailPt) {
    if (headPt == tailPt)
        return;
    int midPt = (headPt + tailPt) >> 1;
    divideConquer(headPt, midPt);
    divideConquer(midPt + 1, tailPt);

    int j = headPt;
    for (int i = midPt + 1; i <= tailPt; i++) {
        if (qArr[i].type == 2)
            continue;
        for (; j <= midPt && qArr[j].x <= qArr[i].x; j++)
            if (qArr[j].type == 2)
                add(qArr[j].y, qArr[j].val);
        ans[qArr[i].val] += (1 - (qArr[i].type << 1)) * prefixSum(qArr[i].y);
    }

    for (int i = headPt; i < j; i++)
        if (qArr[i].type == 2)
            add(qArr[i].y, -qArr[i].val);

    inplace_merge(qArr + headPt, qArr + midPt + 1, qArr + tailPt + 1);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    memset(last, -1, sizeof(last));
    memset(bit, 0, sizeof(bit));
    int len, qNum, ansPt = 0, qPt = 0;
    cin >> len >> qNum;
    for (int i = 0; i < len; i++) {
        cin >> arr[i];
        pre[i] = last[arr[i]];
        qArr[qPt++] = {2, i, pre[i], i - pre[i]};
        last[arr[i]] = i;
        st[arr[i]].insert(i);
    }

    for (int i = 0; i < qNum; i++) {
        int op, x, y;
        cin >> op >> x >> y;
        x--;
        if (op == 1) {  // Modify
            // Erase original
            qArr[qPt++] = {2, x, pre[x], -(x - pre[x])};

            auto it = st[arr[x]].upper_bound(x);
            if (it != st[arr[x]].end()) {
                qArr[qPt++] = {2, *it, pre[*it], -(*it - pre[*it])};
                pre[*it] = pre[x];
                qArr[qPt++] = {2, *it, pre[*it], *it - pre[*it]};
            }

            st[arr[x]].erase(x);

            // Insert new
            it = st[y].upper_bound(x);
            if (it != st[y].end()) {
                pre[x] = pre[*it];
                qArr[qPt++] = {2, x, pre[x], x - pre[x]};
                qArr[qPt++] = {2, *it, pre[*it], -(*it - pre[*it])};
                pre[*it] = x;
                qArr[qPt++] = {2, *it, pre[*it], *it - pre[*it]};
            } else {
                if (st[y].empty()) {
                    pre[x] = -1;
                    qArr[qPt++] = {2, x, pre[x], x - pre[x]};
                } else {
                    it = prev(it);
                    pre[x] = *it;
                    qArr[qPt++] = {2, x, pre[x], x - pre[x]}; 
                }
            }

            st[y].insert(x);
            arr[x] = y;

        } else {    // Query
            y--;
            qArr[qPt++] = {0, y, y, ansPt};
            qArr[qPt++] = {0, x - 1, x - 1, ansPt};
            qArr[qPt++] = {1, x - 1, y, ansPt};
            qArr[qPt++] = {1, y, x - 1, ansPt};
            ansPt++;
        }
    }

    divideConquer(0, qPt - 1);

    for (int i = 0; i < ansPt; i++)
        cout << ans[i] << '\n';
    return 0;
}