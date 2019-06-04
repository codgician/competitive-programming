#include <bits/stdc++.h>
using namespace std;

#define SIZE 100010
#define VAL_SIZE 200020

typedef struct _Node {
    int a, b, c;
    int num, ans;

    bool operator == (const struct _Node & snd) const {
        return a == snd.a && b == snd.b && c == snd.c;
    }
} Node;

Node arr[SIZE];
int ans[SIZE], bit[VAL_SIZE], siz;

bool cmpSnd(Node & fst, Node & snd) {
    if (fst.b != snd.b)
        return fst.b < snd.b;
    return fst.c < snd.c;
}

bool cmpFst(Node & fst, Node & snd) {
    if (fst.a != snd.a)
        return fst.a < snd.a;
    return cmpSnd(fst, snd);
}

int lowbit(int n) {
    return n & -n;
}

void add(int pos, int val) {
    for (int i = pos; i <= siz; i += lowbit(i))
        bit[i] += val;
}

void clear(int pos) {
    for (int i = pos; i <= siz; i += lowbit(i))
        bit[i] = 0;
}

int prefixSum(int pos) {
    int ret = 0;
    for (int i = pos; i > 0; i -= lowbit(i))
        ret += bit[i];
    return ret;
}

void divideConquer(int headPt, int tailPt) {
    if (headPt == tailPt)
        return;

    int midPt = (headPt + tailPt) >> 1;

    if (headPt < midPt)
        divideConquer(headPt, midPt);
    if (midPt + 1 < tailPt)
        divideConquer(midPt + 1, tailPt);

    sort(arr + headPt, arr + midPt + 1, cmpSnd);
    sort(arr + midPt + 1, arr + tailPt + 1, cmpSnd);

    int j = headPt;
    for (int i = midPt + 1; i <= tailPt; i++) {
        for (; j <= midPt && arr[j].b <= arr[i].b; j++)
            add(arr[j].c, arr[j].num);
        arr[i].ans += prefixSum(arr[i].c);
    }

    for (int i = headPt; i < j; i++)
        clear(arr[i].c);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    memset(ans, 0, sizeof(ans));
    memset(bit, 0, sizeof(bit));

    int num;
    cin >> num >> siz;
    for (int i = 0; i < num; i++) {
        cin >> arr[i].a >> arr[i].b >> arr[i].c;
        arr[i].num = 1; arr[i].ans = 0;
    }

    sort(arr + 0, arr + num, cmpFst);

    int ovrPt = 0, cntPt = 1;
    while (cntPt < num) {
        if (arr[ovrPt] == arr[cntPt])
            arr[ovrPt].num += arr[cntPt].num;
        else
            arr[++ovrPt] = arr[cntPt];
        cntPt++;
    }
    ovrPt++;

    divideConquer(0, ovrPt - 1);
    for (int i = 0; i < ovrPt; i++) {
        arr[i].ans += arr[i].num - 1;
        ans[arr[i].ans] += arr[i].num;
    }
    for (int i = 0; i < num; i++)
        cout << ans[i] << '\n';
    return 0;
}