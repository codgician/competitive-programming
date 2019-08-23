#include <bits/stdc++.h>
using namespace std;

#define SIZE 10000010
const int mod = 998244353;

template<typename T>
bool read(T & ret) {
    char ch; int sgn;
    if (ch = getchar(), ch == EOF)
        return false;
    while (ch != '-' && (ch < '0' || ch > '9'))
        ch = getchar();
    sgn = (ch == '-') ? -1 : 1;  ret = (ch == '-') ? 0 : (ch - '0');
    while (ch = getchar(), ch >= '0' && ch <= '9')
        ret = ret * 10 + (ch - '0');
    ret *= sgn;
    return true;
}

template<typename T>
void print(T x) {
    if(x < 0) {
        x = -x; putchar('-');
    }
    if(x > 9)
        print(x / 10);
    putchar(x % 10 + '0');
}

int minFacArr[SIZE], primeArr[SIZE], phi[SIZE], primePt;

void initPhi() {
    memset(minFacArr, 0, sizeof(minFacArr));
    primePt = 0; phi[1] = 1;
    for (int i = 2; i < SIZE; i++) {
        if (minFacArr[i] == 0) {
            minFacArr[i] = i;
            primeArr[primePt++] = i;
            phi[i] = i - 1;
        }
        for (int j = 0; j < primePt && primeArr[j] <= min(minFacArr[i], (SIZE - 1) / i); j++) {
            minFacArr[i * primeArr[j]] = primeArr[j];
            if (minFacArr[i] == primeArr[j]) {
                phi[i * primeArr[j]] = phi[i] * primeArr[j];
            } else {
                phi[i * primeArr[j]] = phi[i] * (primeArr[j] - 1);
            }
        }
    }
}

int cbrt(__int128 n) {
    int leftPt = 0, rightPt = SIZE; int ans = -1;
    while (leftPt <= rightPt) {
        int midPt = (leftPt + rightPt) >> 1;
        if ((__int128)midPt * midPt * midPt <= n) {
            ans = midPt; leftPt = midPt + 1;
        } else {
            rightPt = midPt - 1;
        }
    }
    return ans;
}

long long int calc1(int n) {
    return (n & 1 ? 1ll * ((n + 1) >> 1) * n : 1ll * (n >> 1) * (n + 1));
}

long long int calc2(int n) {
    long long int ret = calc1(n);
    return (ret % 3 == 0 ? (ret / 3) % mod * ((n << 1) + 1) : ret % mod * (((n << 1) + 1) / 3)) % mod;
}

int main() {
    int caseNum; read(caseNum);
    initPhi();
    while (caseNum--) {
        __int128 n; read(n);

        int cbrtN = cbrt(n); long long int ans = 0;
        for (int t = 1; (__int128)t * t * t < n; t++) {
            int r = (cbrtN - 1) / t;
            ans = (ans + phi[t] * (3 * t * calc2(r) + 3 * (calc1(r) % mod) + r)) % mod;
        }
        
        int a = cbrtN; __int128 n1 = n, n2 = (__int128)a * a * a - 1;
        for (int t = 1; t * t <= a; t++) {
            if (a % t != 0)
                continue;
            ans = (ans + phi[t] * (long long int)((n1 / t - n2 / t) % mod)) % mod;
            if (t * t != a) {
                int t1 = a / t;
                ans = (ans + phi[t1] * (long long int)((n1 / t1 - n2 / t1) % mod)) % mod;
            } 
        }
        
        print(ans); putchar('\n');
    }
    return 0;
}