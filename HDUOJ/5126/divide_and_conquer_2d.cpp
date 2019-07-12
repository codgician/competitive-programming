#include <bits/stdc++.h>
using namespace std;

#define SIZE 50010
#define Q_SIZE 500010

typedef struct _Query {
    int id, sgn, x, y, z;
    bool flag;
} Query;
Query qArr[Q_SIZE], tmp[Q_SIZE];

bool cmpSnd(const Query & fst, const Query & snd) {
    if (fst.y != snd.y)
        return fst.y < snd.y;
    return fst.z < snd.z; 
}

bool cmpFst(const Query & fst, const Query & snd) {
    if (fst.x != snd.x)
        return fst.x < snd.x;
    return cmpSnd(fst, snd);
}

int bit[Q_SIZE], ans[SIZE], dsc[Q_SIZE];

int lowbit(int n) {
    return n & -n;
}

void add(int pos, int val) {
    pos++;
    for (int i = pos; i < Q_SIZE; i += lowbit(i))
        bit[i] += val;
}

int prefixSum(int pos) {
    int ret = 0; pos++;
    for (int i = pos; i > 0; i -= lowbit(i))
        ret += bit[i];
    return ret;
}

void divideConquer2(int headPt, int tailPt) {
    if (headPt == tailPt)
        return;
    int midPt = (headPt + tailPt) >> 1;
    divideConquer2(headPt, midPt);
    divideConquer2(midPt + 1, tailPt);

    int j = headPt;
    for (int i = midPt + 1; i <= tailPt; i++) {
        if (qArr[i].id == -1 || qArr[i].flag == false)
            continue;
        for (; j <= midPt && qArr[j].y <= qArr[i].y; j++)
            if (qArr[j].id == -1 && qArr[j].flag == false)
                add(qArr[j].z, qArr[j].sgn);
        ans[qArr[i].id] += qArr[i].sgn * prefixSum(qArr[i].z);
    }

    for (int i = headPt; i < j; i++)
        if (qArr[i].id == -1 && qArr[i].flag == false)
            add(qArr[i].z, -qArr[i].sgn);

    inplace_merge(qArr + headPt, qArr + midPt + 1, qArr + tailPt + 1, cmpSnd);
}

void divideConquer(int headPt, int tailPt) {
    if (headPt == tailPt)
        return;
    int midPt = (headPt + tailPt) >> 1;
    divideConquer(headPt, midPt);
    divideConquer(midPt + 1, tailPt);

    for (int i = headPt; i <= midPt; i++)
        qArr[i].flag = false;
    for (int i = midPt + 1; i <= tailPt; i++)
        qArr[i].flag = true;

    inplace_merge(qArr + headPt, qArr + midPt + 1, qArr + tailPt + 1, cmpFst);
    copy(qArr + headPt, qArr + tailPt + 1, tmp + headPt);
    divideConquer2(headPt, tailPt);
    copy(tmp + headPt, tmp + tailPt + 1, qArr + headPt);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int caseNum; cin >> caseNum;
    while (caseNum--) {
        int qNum, qPt = 0, idPt = 0, dscPt = 0; 
        cin >> qNum;
        for (int i = 0; i < qNum; i++) {
            int op, x, y, z; cin >> op >> x >> y >> z;
            if (op == 1) {
                // Add vertex
                qArr[qPt++] = {-1, 1, x, y, z, false};
                dsc[dscPt++] = z;
            } else {
                // Query
                int x1, y1, z1; cin >> x1 >> y1 >> z1;
                qArr[qPt++] = {idPt, 1, x1, y1, z1, false};
                qArr[qPt++] = {idPt, -1, x - 1, y1, z1, false};
                qArr[qPt++] = {idPt, -1, x1, y - 1, z1, false};
                qArr[qPt++] = {idPt, -1, x1, y1, z - 1, false};
                qArr[qPt++] = {idPt, 1, x - 1, y - 1, z1, false};
                qArr[qPt++] = {idPt, 1, x - 1, y1, z - 1, false};
                qArr[qPt++] = {idPt, 1, x1, y - 1, z - 1, false};
                qArr[qPt++] = {idPt, -1, x - 1, y - 1, z - 1, false};
                dsc[dscPt++] = z1; dsc[dscPt++] = z - 1;
                ans[idPt++] = 0;
            }
        }

        sort(dsc + 0, dsc + dscPt);
        dscPt = unique(dsc + 0, dsc + dscPt) - dsc;
        for (int i = 0; i < qPt; i++)
            qArr[i].z = lower_bound(dsc + 0, dsc + dscPt, qArr[i].z) - dsc;

        divideConquer(0, qPt - 1);
        for (int i = 0; i < idPt; i++)
            cout << ans[i] << '\n';
    }

    return 0;
}