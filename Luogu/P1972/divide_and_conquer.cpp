#include <bits/stdc++.h>
using namespace std;

#define SIZE 500010
#define Q_SIZE 2500010
#define VAL_SIZE 1000010

typedef struct _Query {
    int id, sgn;
    int x, y;
} Query;

Query qArr[Q_SIZE];

int pre[SIZE], last[VAL_SIZE], ans[SIZE];

bool cmpSnd(const Query & fst, const Query & snd) {
    if (fst.y != snd.y)
        return fst.y < snd.y;
    return fst.id < snd.id;
}

bool cmpFst(const Query & fst, const Query & snd) {
    if (fst.x != snd.x)
        return fst.x < snd.x;
    return cmpSnd(fst, snd);
}

void divideConquer(int headPt, int tailPt) {
    if (headPt == tailPt)
        return;
    int midPt = (headPt + tailPt) >> 1;
    divideConquer(headPt, midPt);
    divideConquer(midPt + 1, tailPt);

    int j = headPt, cntNum = 0;
    for (int i = midPt + 1; i <= tailPt; i++) {
        if (qArr[i].id == -1)
            continue;
        for (; j <= midPt && qArr[j].y <= qArr[i].y ; j++)
            if (qArr[j].id == -1) 
                cntNum++;
        ans[qArr[i].id] += qArr[i].sgn * cntNum;
    }

    inplace_merge(qArr + headPt, qArr + midPt + 1, qArr + tailPt + 1, cmpSnd);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    memset(last, -1, sizeof(last));
    memset(ans, 0, sizeof(ans));
    int len, qNum, qPt = 0;
    cin >> len;
    for (int i = 0; i < len; i++) {
        int cnt; cin >> cnt;
        pre[i] = last[cnt];
        last[cnt] = i;
        qArr[qPt++] = {-1, 0, i, pre[i]};
    }

    cin >> qNum;
    for (int i = 0; i < qNum; i++) {
        int x, y; cin >> x >> y;
        x--; y--;
        qArr[qPt++] = {i, 1, y, x - 1};
        qArr[qPt++] = {i, -1, x - 1, x - 1};
    }
    sort(qArr + 0, qArr + qPt, cmpFst);

    divideConquer(0, qPt - 1);

    for (int i = 0; i < qNum; i++)
        cout << ans[i] << '\n';
    return 0;
}
