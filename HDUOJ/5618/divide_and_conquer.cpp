#include <bits/stdc++.h>
using namespace std;

#define SIZE 100010

typedef struct _Node {
    int id, x, y, z;
} Node;

Node arr[SIZE];
int ans[SIZE], bit[SIZE], len;

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
    if (fst.y != snd.y)
        return fst.y < snd.y;
    return fst.z < snd.z;
}

bool cmpFst(Node & fst, Node & snd) {
    if (fst.x == snd.x)
        return cmpSnd(fst, snd);
    return fst.x < snd.x;
}

void divideConquer(int headPt, int tailPt) {
    if (headPt == tailPt)
        return;

    int midPt = (headPt + tailPt) >> 1;
    divideConquer(headPt, midPt);
    divideConquer(midPt + 1, tailPt);

    int j = headPt;
    for (int i = midPt + 1; i <= tailPt; i++) {
        for (; j <= midPt && arr[j].y <= arr[i].y; j++)
            add(arr[j].z, 1);
        ans[arr[i].id] += prefixSum(arr[i].z);
    }

    for (int i = headPt; i < j; i++)
        add(arr[i].z, -1);

    inplace_merge(arr + headPt, arr + midPt + 1, arr + tailPt + 1, cmpSnd);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int caselen; cin >> caselen;
    while (caselen--) {
        memset(ans, 0, sizeof(ans));
        memset(bit, 0, sizeof(bit));

        cin >> len;
        for (int i = 0; i < len; i++) {
            arr[i].id = i;
            cin >> arr[i].x >> arr[i].y >> arr[i].z;
        }

        sort(arr + 0, arr + len, cmpFst);
        divideConquer(0, len - 1);

        sort(arr + 0, arr + len, cmpFst);
        for (int i = len - 2; i >= 0; i--) {
            if (arr[i].x == arr[i + 1].x && arr[i].y == arr[i + 1].y && arr[i].z == arr[i + 1].z) {
                ans[arr[i].id] = ans[arr[i + 1].id];
            }
        }

        for (int i = 0; i < len; i++)
            cout << ans[i] << '\n';
    }

    return 0;
}