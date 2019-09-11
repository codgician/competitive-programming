#include <bits/stdc++.h>
using namespace std;

#define SIZE 200010

class Query {
public:
    int id, pos, leftPt, rightPt;
};

Query ques[SIZE << 1];
int arr[SIZE], ans[SIZE], pos[SIZE], len;
int bit[SIZE];

int lowbit(int n) {
    return n & -n;
}

void add(int pos, int val) {
    pos++;
    for (int i = pos; i <= len + 1; i += lowbit(i))
        bit[i] += val;
}

int prefixSum(int pos) {
    int ret = 0; pos++;
    for (int i = pos; i > 0; i -= lowbit(i))
        ret += bit[i];
    return ret;
}

int rangeSum(int qLeftPt, int qRightPt) {
    return prefixSum(qRightPt) - prefixSum(qLeftPt - 1);
}

int primes[SIZE], minFac[SIZE], primesPt;

void initPrimes() {
    memset(minFac, 0, sizeof(minFac)); primesPt = 0;
    for (int i = 2; i < SIZE; i++) {
        if (minFac[i] == 0) 
            minFac[i] = i, primes[primesPt++] = i;
        for (int j = 0; j < primesPt && primes[j] <= min(minFac[i], (SIZE - 1) / i); j++)
            minFac[i * primes[j]] = primes[j];
    }
}

bool cmpSnd(const Query & fst, const Query & snd) {
    if (fst.rightPt != snd.rightPt)
        return fst.rightPt > snd.rightPt;
    if (fst.id != snd.id)
        return fst.id < snd.id;
    return fst.pos < snd.pos;
}

bool cmpFst(const Query & fst, const Query & snd) {
    if (fst.leftPt != snd.leftPt)
        return fst.leftPt < snd.leftPt;
    return cmpSnd(fst, snd);
}

void divideConquer(int headPt, int tailPt) {
    if (headPt == tailPt)
        return;
    int midPt = (headPt + tailPt) >> 1;
    divideConquer(headPt, midPt);
    divideConquer(midPt + 1, tailPt);

    int j = headPt;
    for (int i = midPt + 1; i <= tailPt; i++) {
        if (ques[i].id == -1)
            continue;
        for (; j <= midPt && ques[j].rightPt >= ques[i].rightPt; j++)
            if (ques[j].id == -1) 
                add(ques[j].pos, 1);
        ans[ques[i].id] += rangeSum(ques[i].leftPt, ques[i].rightPt);
    }

    for (int i = headPt; i < j; i++)
        if (ques[i].pos != -1)
            add(ques[i].pos, -1);

    inplace_merge(ques + headPt, ques + midPt + 1, ques + tailPt + 1, cmpSnd);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int qNum; initPrimes();
    while (cin >> len >> qNum) {
        if (len == 0 && qNum == 0)
            break;
        for (int i = 0; i < len; i++)
            cin >> arr[i], ques[i] = Query{-1, i, -1, len};
        // Left
        fill(pos + 0, pos + SIZE, -1);
        for (int i = 0; i < len; i++) {
            int cnt = arr[i];
            while (cnt > 1) {
                int p = minFac[cnt]; cnt /= p;
                while (cnt > 1 && minFac[cnt] == p)
                    cnt /= p;
                ques[i].leftPt = max(ques[i].leftPt, pos[p]), pos[p] = i;
            }
        }
        // Right
        fill(pos + 0, pos + SIZE, len);
        for (int i = len - 1; i >= 0; i--) {
            int cnt = arr[i];
            while (cnt > 1) {
                int p = minFac[cnt]; cnt /= p;
                while (cnt > 1 && minFac[cnt] == p)
                    cnt /= p;
                ques[i].rightPt = min(ques[i].rightPt, pos[p]), pos[p] = i;
            }
        }
        for (int i = 0; i < len; i++)
            ques[i].leftPt++, ques[i].rightPt--;

        for (int i = 0; i < qNum; i++) {
            int qLeftPt, qRightPt; cin >> qLeftPt >> qRightPt;
            qLeftPt--; qRightPt--; ques[i + len] = Query{i, -1, qLeftPt, qRightPt};
        }

        int qPt = qNum + len;
        sort(ques + 0, ques + qPt, cmpFst);
        fill(bit + 0, bit + len + 2, 0);
        fill(ans + 0, ans + qNum, 0);
        divideConquer(0, qPt - 1);

        for (int i = 0; i < qNum; i++)
            cout << ans[i] << '\n';
    }

    return 0;
}