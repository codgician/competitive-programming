#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <string>
#include <cstring>
#include <iomanip>
#include <climits>
#include <stack>
#include <queue>
#include <vector>
#include <set>
#include <map>
#include <functional>
#include <iterator>
#include <cassert>
using namespace std;

#define SIZE 50010

#define LEFT false
#define RIGHT true

typedef struct _Node {
    int val[4];
    bool flag;
    bool operator == (const struct _Node & snd) const {
        for (int i = 0; i < 4; i++)
            if (val[i] != snd.val[i])
                return false;
        return true;
    }
} Node;

bool cmpThd(const Node & fst, const Node & snd) {
    if (fst.val[2] != snd.val[2])
        return fst.val[2] < snd.val[2];
    return fst.val[3] < snd.val[3];
}

bool cmpSnd(const Node & fst, const Node & snd) {
    if (fst.val[1] != snd.val[1])
        return fst.val[1] < snd.val[1];
    return cmpThd(fst, snd);
}

Node arr[SIZE], tmp[SIZE];
int bit[SIZE], siz, ans;

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

void divideConquer2D(int headPt, int tailPt) {
    if (headPt >= tailPt)
        return;

    int midPt = (headPt + tailPt) >> 1;

    divideConquer2D(headPt, midPt);
    divideConquer2D(midPt + 1, tailPt);

    sort(arr + headPt, arr + midPt + 1, cmpThd);
    sort(arr + midPt + 1, arr + tailPt + 1, cmpThd);

    int j = headPt;
    for (int i = midPt + 1; i <= tailPt; i++) {
        for (; j <= midPt && arr[j].val[2] < arr[i].val[2]; j++)
            if (arr[j].flag == LEFT)
                add(arr[j].val[3], 1);
        if (arr[i].flag == RIGHT)
            ans += prefixSum(arr[i].val[3]);
    }

    for (int i = headPt; i < j; i++)
        if (arr[i].flag == LEFT)
            clear(arr[i].val[3]);
}

void divideConquer3D(int headPt, int tailPt) {
    if (headPt >= tailPt)
        return;

    int midPt = (headPt + tailPt) >> 1;

    divideConquer3D(headPt, midPt);
    divideConquer3D(midPt + 1, tailPt);

    sort(arr + headPt, arr + midPt + 1, cmpSnd);
    sort(arr + midPt + 1, arr + tailPt + 1, cmpSnd);

    int leftPt = headPt, rightPt = midPt + 1, tmpPt = 0;
    while (leftPt <= midPt && rightPt <= tailPt) {
        if (arr[leftPt].val[1] < arr[rightPt].val[1]) {
            tmp[tmpPt] = arr[leftPt++];
            tmp[tmpPt++].flag = LEFT;
        } else {
            tmp[tmpPt] = arr[rightPt++];
            tmp[tmpPt++].flag = RIGHT;
        }
    }
    while (leftPt <= midPt) {
        tmp[tmpPt] = arr[leftPt++];
        tmp[tmpPt++].flag = LEFT;
    }
    while (rightPt <= tailPt) {
        tmp[tmpPt] = arr[rightPt++];
        tmp[tmpPt++].flag = RIGHT;
    }

    for (int i = 0; i < tmpPt; i++)
        arr[headPt + i] = tmp[i];
    divideConquer2D(headPt, tailPt);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    memset(bit, 0, sizeof(bit));
    siz = 0, ans = 0;
    int num;
    cin >> num;
    for (int j = 1; j < 4; j++) {
        for (int i = 0; i < num; i++) {
            cin >> arr[i].val[j];
            arr[i].val[0] = i;
            siz = max(siz, arr[i].val[j]);
        }
    }
    divideConquer3D(0, num - 1);
    cout << ans << '\n';
    return 0;
}