#include <bits/stdc++.h>
using namespace std;

#define SUZE 10010

const int mod = 1e9 + 7;

long long int fastPow(long long int a, long long int n) {
    long long int ans = 1;
    while (n > 0) {
        if (n & 1)
            ans = ans * a % mod;
        a = a * a % mod;
        n >>= 1;
    }
    return ans;
}

int phi(int num) {
    int ret = num;
    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0) {
            ret -= ret / i;
            while (num % i == 0)
                num /= i;
        }
    }
    if (num > 1)
        ret -= ret / num;
    return ret;
}

vector<int> fac;

void getFac(int num) {
    fac.clear();
    for (int i = 1; i * i <= num; i++) {
        if (num % i == 0) {
            fac.push_back(i);
            if (i * i != num)
                fac.push_back(num / i);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int caseNum;
    cin >> caseNum;
    for (int t = 1; t <= caseNum; t++) {
        int n, m;
        cin >> m >> n;
        getFac(n);

        long long int ans = 0;
        for (auto i : fac)
            ans = (ans + phi(n / i) * fastPow(m, i) % mod) % mod;
        if (n & 1)
            ans = (ans + n * fastPow(m, ((n - 1) >> 1) + 1) % mod) % mod;
        else
            ans = (ans + (n >> 1) * (fastPow(m, (n >> 1) + 1) + fastPow(m, n >> 1)) % mod) % mod; 

        cout << "Case #" << t << ": " << ans * fastPow(n << 1, mod - 2) % mod << '\n'; 
        
    }
    return 0;
}
