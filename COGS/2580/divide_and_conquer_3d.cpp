#include <bits/stdc++.h>
using namespace std;

#define SIZE 50010

#define LEFT 0
#define RIGHT 1

typedef struct _Node {
    int val[5];
    bool type[2];
} Node;

bool cmpFor(const Node & fst, const Node & snd) {
    if (fst.val[3] != snd.val[3])
        return fst.val[3] < snd.val[3];
    return fst.val[4] < snd.val[4];
}

bool cmpThd(const Node & fst, const Node & snd) {
    if (fst.val[2] != snd.val[2])
        return fst.val[2] < snd.val[2];
    return cmpFor(fst, snd);
}

bool cmpSnd(const Node & fst, const Node & snd) {
    if (fst.val[1] != snd.val[1])
        return fst.val[1] < snd.val[1];
    return cmpThd(fst, snd);
}

Node arr[SIZE], tmp1[SIZE], tmp2[SIZE];
int bit[SIZE], ans;

int lowbit(int n) {
    return n & -n;
}

void add(int pos, int val) {
    for (int i = pos; i < SIZE; i += lowbit(i))
        bit[i] += val;
}

int prefixSum(int pos) {
    int ret = 0;
    for (int i = pos; i > 0; i -= lowbit(i))
        ret += bit[i];
    return ret;
}

void divideConquer2D(int headPt, int tailPt) {
    if (headPt == tailPt)
        return;
    int midPt = (headPt + tailPt) >> 1;
    divideConquer2D(headPt, midPt);
    divideConquer2D(midPt + 1, tailPt);

    int j = headPt;
    for (int i = midPt + 1; i <= tailPt; i++) {
        if (arr[i].type[0] == LEFT || arr[i].type[1] == LEFT)
            continue;
        for (; j <= midPt && arr[j].val[3] < arr[i].val[3]; j++)
            if (arr[j].type[0] == LEFT && arr[j].type[1] == LEFT)
                add(arr[j].val[4], 1);
        ans += prefixSum(arr[i].val[4]);
    }

    for (int i = headPt; i < j; i++)
        if (arr[i].type[0] == LEFT && arr[i].type[1] == LEFT)
            add(arr[i].val[4], -1);

    inplace_merge(arr + headPt, arr + midPt + 1, arr + tailPt + 1, cmpFor);
}

void divideConquer3D(int headPt, int tailPt) {
    if (headPt == tailPt)
        return;
    int midPt = (headPt + tailPt) >> 1;
    divideConquer3D(headPt, midPt);
    divideConquer3D(midPt + 1, tailPt);

    for (int i = headPt; i <= midPt; i++)
        arr[i].type[1] = LEFT;
    for (int i = midPt + 1; i <= tailPt; i++)
        arr[i].type[1] = RIGHT;

    inplace_merge(arr + headPt, arr + midPt + 1, arr + tailPt + 1, cmpThd);
    copy(arr + headPt, arr + tailPt + 1, tmp2 + headPt);
    divideConquer2D(headPt, tailPt);
    copy(tmp2 + headPt, tmp2 + tailPt + 1, arr + headPt);
}

void divideConquer4D(int headPt, int tailPt) {
    if (headPt == tailPt)
        return;
    int midPt = (headPt + tailPt) >> 1;
    divideConquer4D(headPt, midPt);
    divideConquer4D(midPt + 1, tailPt);

    for (int i = headPt; i <= midPt; i++)
        arr[i].type[0] = LEFT;
    for (int i = midPt + 1; i <= tailPt; i++)
        arr[i].type[0] = RIGHT;

    inplace_merge(arr + headPt, arr + midPt + 1, arr + tailPt + 1, cmpSnd);
    copy(arr + headPt, arr + tailPt + 1, tmp1 + headPt);
    divideConquer3D(headPt, tailPt);
    copy(tmp1 + headPt, tmp1 + tailPt + 1, arr + headPt);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    freopen("partial_order_two.in", "r", stdin);
    freopen("partial_order_two.out", "w", stdout);

    memset(bit, 0, sizeof(bit));
    int num; ans = 0;
    cin >> num;
    for (int j = 1; j < 5; j++) {
        for (int i = 0; i < num; i++) {
            cin >> arr[i].val[j];
            arr[i].val[0] = i;
        }
    }

    divideConquer4D(0, num - 1);
    cout << ans << '\n';
    return 0;
}