#include<bits/stdc++.h>
using namespace std;

#define SIZE 100010

const int mod = 1e9 + 7;

long long int fastPow(long long int a, long long int n, long long int mod) {
    long long int ret = 1; a %= mod;
    while (n > 0) {
        if (n & 1)
            ret = (ret * a) % mod;
        a = (a * a) % mod; n >>= 1;
    }
    return ret;
}

long long int numbers[SIZE], factorials[SIZE], invFactorials[SIZE];

void init(int len, int base) {
    numbers[0] = 0; numbers[1] = 1; long long int cnt = base;
    for (int i = 2; i <= len; i++) {
        numbers[i] = (numbers[i - 1] + cnt) % mod;
        cnt = cnt * base % mod;
    }

    factorials[0] = 1;
    for (int i = 1; i <= len; i++)
        factorials[i] = factorials[i - 1] * numbers[i] % mod;
    invFactorials[len] = fastPow(factorials[len], mod - 2, mod);
    for (int i = len - 1; i >= 0; i--)
        invFactorials[i] = invFactorials[i + 1] * numbers[i + 1] % mod;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int len, base; cin >> len >> base; 
    unordered_map<int, int> mp; init(len, base);
    for (int i = 0; i < len; i++) {
        int cnt; cin >> cnt; mp[cnt]++;
    }

    long long int ret = factorials[len];
    for (const auto & p : mp)
        ret = ret * invFactorials[p.second] % mod;
    cout << ret << '\n';

    return 0;
}