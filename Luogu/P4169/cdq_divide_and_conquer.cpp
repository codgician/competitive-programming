// luogu-judger-enable-o2
#include <bits/stdc++.h>
using namespace std;

#define SIZE 1000010
#define Q_SIZE 600020

typedef struct _Query {
    int id, x, y;
    bool operator < (const struct _Query & snd) const {
        if (x != snd.x)
            return x < snd.x;
        if (y != snd.y)
            return y < snd.y;
        return id < snd.id;
    }
} Query;

Query qArr[Q_SIZE], orig[Q_SIZE];

int bit[SIZE], ans[Q_SIZE];

int lowbit(int n) {
    return n & -n;
}

void addMax(int pos, int val) {
    pos++;
    for (int i = pos; i < SIZE; i += lowbit(i))
        bit[i] = max(bit[i], val);
}

void clear(int pos) {
    pos++;
    for (int i = pos; i < SIZE; i += lowbit(i))
        bit[i] = INT_MIN;
}

int prefixMax(int pos) {
    int ret = INT_MIN; pos++;
    for (int i = pos; i > 0; i -= lowbit(i))
        ret = max(ret, bit[i]);
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
        if (qArr[i].id == -1)
            continue;
        for (; j <= midPt && qArr[j].x <= qArr[i].x; j++)
            if (qArr[j].id == -1)
                addMax(qArr[j].y, qArr[j].x + qArr[j].y);
        int ret = prefixMax(qArr[i].y);
        if (ret != INT_MIN)
            ans[qArr[i].id] = min(ans[qArr[i].id], qArr[i].x + qArr[i].y - ret);
    }

    for (int i = headPt; i < j; i++)
        if (qArr[i].id == -1)
            clear(qArr[i].y);

    inplace_merge(qArr + headPt, qArr + midPt + 1, qArr + tailPt + 1);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int len, qNum; cin >> len >> qNum;
    for (int i = 0; i < len; i++) {
        cin >> qArr[i].x >> qArr[i].y;
        qArr[i].id = -1;
    }

    int qPt = len, idPt = 0;
    for (int i = 0; i < qNum; i++) {
        int op; cin >> op >> qArr[qPt].x >> qArr[qPt].y;
        qArr[qPt++].id = (op == 1 ? -1 : idPt++);
    }

    fill(bit + 0, bit + SIZE, INT_MIN);
    fill(ans + 0, ans + idPt, INT_MAX);
    copy(qArr + 0, qArr + qPt, orig + 0);

    // (x1 + y1) - (x2 + y2)
    divideConquer(0, qPt - 1);

    // (x1 - y1) + (x2 - y2)
    for (int i = 0; i < qPt; i++) {
       qArr[i] = orig[i];
       qArr[i].y = SIZE - 1 - qArr[i].y;
    }
    divideConquer(0, qPt - 1);

    // (-x1 + y1) + (-x2 + y2)
    for (int i = 0; i < qPt; i++) {
        qArr[i] = orig[i];
        qArr[i].x = SIZE - 1 - qArr[i].x;
    }
    divideConquer(0, qPt - 1);

    // (-x1 - y1) + (-x2 - y2)
    copy(orig + 0, orig + qPt, qArr + 0);
    for (int i = 0; i < qPt; i++) {
        qArr[i] = orig[i];
        qArr[i].x = SIZE - 1 - qArr[i].x;
        qArr[i].y = SIZE - 1 - qArr[i].y;
    }
    divideConquer(0, qPt - 1);

    for (int i = 0; i < idPt; i++)
        cout << ans[i] << '\n';
    return 0;
}