#include <bits/stdc++.h>
using namespace std;

#define SIZE 4000

int primeArr[SIZE], minFacArr[SIZE], primePt;
void initPrime() {
    memset(minFacArr, 0, sizeof(minFacArr));
    primePt = 0;
    for (int i = 2; i < SIZE; i++) {
        if (minFacArr[i] == 0) {
            minFacArr[i] = i;
            primeArr[primePt++] = i;
        }
        for (int j = 0; j < primePt && primeArr[j] <= min(minFacArr[i], (SIZE - 1) / i); j++) {
            minFacArr[i * primeArr[j]] = primeArr[j];
        }
    }
}

int sq2rt(long long int num) {
    int leftPt = 1, rightPt = 31624, ret = -1;
    while (leftPt <= rightPt) {
        int midPt = (leftPt + rightPt) >> 1;
        if (1ll * midPt * midPt * midPt * midPt <= num) {
            ret = midPt; leftPt = midPt + 1;
        } else {
            rightPt = midPt - 1;
        }
    }
    return ret;
}

int cbrt(long long int num) {
    int leftPt = 1, rightPt = 1e6 + 1, ret = -1;
    while (leftPt <= rightPt) {
        int midPt = (leftPt + rightPt) >> 1;
        if (1ll * midPt * midPt * midPt <= num) {
            ret = midPt; leftPt = midPt + 1;
        } else {
            rightPt = midPt - 1;
        }
    }
    return ret;
}

int sqrt(long long int num) {
    int leftPt = 1, rightPt = 1e9 + 1, ret = -1;
    while (leftPt <= rightPt) {
        int midPt = (leftPt + rightPt) >> 1;
        if (1ll * midPt * midPt <= num) {
            ret = midPt; leftPt = midPt + 1;
        } else {
            rightPt = midPt - 1;
        }
    }
    return ret;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    initPrime();

    int caseNum; cin >> caseNum;
    while (caseNum--) {
        long long int num; cin >> num;

        long long int cnt = num; int ret = INT_MAX;
        for (int i = 0; i < primePt && 1ll * primeArr[i] * primeArr[i] <= cnt; i++) {
            if (cnt % primeArr[i] != 0)
                continue;
            int exp = 1; cnt /= primeArr[i];
            while (cnt % primeArr[i] == 0)
                cnt /= primeArr[i], exp++;
            ret = min(ret, exp);
        }

        if (cnt < SIZE) {
            if (cnt > 1)
                ret = 1;
            cout << ret << '\n';
            continue;
        }
        
        int sq2Root = sq2rt(num);
        if (1ll * sq2Root * sq2Root * sq2Root * sq2Root == num) {
            cout << 4 << '\n';
            continue;
        }

        int cbRoot = cbrt(num);
        if (1ll * cbRoot * cbRoot * cbRoot == num) {
            cout << 3 << '\n';
            continue;
        }

        int sqRoot = sqrt(num);
        if (1ll * sqRoot * sqRoot == num) {
            cout << 2 << '\n';
            continue;
        }
        cout << 1 << '\n';
    }

    return 0;
}