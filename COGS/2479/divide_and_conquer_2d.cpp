#include <bits/stdc++.h>
using namespace std;

#define SIZE 50010
#define LEFT 0
#define RIGHT 1

typedef struct _Node {
    int id, a, b, c;
    bool type;
} Node;

Node arr[SIZE], tmp[SIZE];
int bit[SIZE], ans, len;

int lowbit(int n) {
    return n & -n;
}

void add(int pos, int val) {
    pos++;
    for (int i = pos; i < SIZE; i += lowbit(i))
        bit[i] += val;
}

int prefixSum(int pos) {
    int ret = 0; pos++;
    for (int i = pos; i > 0; i -= lowbit(i))
        ret += bit[i];
    return ret;
}

bool cmpSnd(const Node & fst, const Node & snd) {
    if (fst.b != snd.b)
        return fst.b < snd.b;
    return fst.c < snd.c; 
}

bool cmpFst(const Node & fst, const Node & snd) {
    if (fst.a != snd.a)
        return fst.a < snd.a;
    return cmpSnd(fst, snd);
}

void divideConquer2D(int headPt, int tailPt) {
    if (headPt == tailPt)
        return;
    int midPt = (headPt + tailPt) >> 1;
    divideConquer2D(headPt, midPt);
    divideConquer2D(midPt + 1, tailPt);

    int j = headPt;
    for (int i = midPt + 1; i <= tailPt; i++) {
        if (arr[i].type == LEFT)
            continue;
        for (; j <= midPt && arr[j].b < arr[i].b; j++)
            if (arr[j].type == LEFT)
                add(arr[j].c, 1);
        ans += prefixSum(arr[i].c);
    }

    for (int i = headPt; i < j; i++)
        if (arr[i].type == LEFT)
            add(arr[i].c, -1);

    inplace_merge(arr + headPt, arr + midPt + 1, arr + tailPt + 1, cmpSnd);
}

void divideConquer3D(int headPt, int tailPt) {
    if (headPt == tailPt)
        return;
    int midPt = (headPt + tailPt) >> 1;
    divideConquer3D(headPt, midPt);
    divideConquer3D(midPt + 1, tailPt);

    for (int i = headPt; i <= midPt; i++)
        arr[i].type = LEFT;
    for (int i = midPt + 1; i <= tailPt; i++)
        arr[i].type = RIGHT;

    inplace_merge(arr + headPt, arr + midPt + 1, arr + tailPt + 1, cmpFst);
    copy(arr + headPt, arr + tailPt + 1, tmp + headPt);
    divideConquer2D(headPt, tailPt);
    copy(tmp + headPt, tmp + tailPt + 1, arr + headPt);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    freopen("partial_order.in", "r", stdin);
    freopen("partial_order.out", "w", stdout);

    memset(bit, 0, sizeof(bit));
    int len; ans = 0; cin >> len;
    for (int i = 0; i < len; i++)
        cin >> arr[i].a;
    for (int i = 0; i < len; i++)
        cin >> arr[i].b;
    for (int i = 0; i < len; i++) {
        cin >> arr[i].c;
        arr[i].id = i;
    }

    divideConquer3D(0, len - 1);
    cout << ans << '\n';
    return 0;
}