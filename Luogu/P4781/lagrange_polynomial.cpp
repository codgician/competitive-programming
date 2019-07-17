#include <bits/stdc++.h>
using namespace std;

#define SIZE 2010

const int mod = 998244353;

pair<int, int> arr[SIZE];
long long int lag[SIZE];
int num;

long long int fastPow(long long int a, long long int n) {
    long long int ret = 1;
    a %= mod;
    while (n > 0) {
        if (n & 1)
            ret = (ret * a) % mod;
        a = (a * a) % mod;
        n >>= 1;
    }
    return ret;
}

void initLag() {
    for (int i = 0; i < num; i++) {
        lag[i] = arr[i].second % mod;
        for (int j = 0; j < num; j++) {
            if (i == j)
                continue;
            lag[i] = lag[i] * fastPow(arr[i].first - arr[j].first , mod - 2) % mod;
        }
    }
}

long long int lagrange(int x) {
    long long int ret = 0;
    for (int i = 0; i < num; i++)
        ret = (ret + lag[i] * fastPow(x - arr[i].first, mod - 2)) % mod;
    for (int i = 0; i < num; i++)
        ret = ret * (x - arr[i].first) % mod;
    return (ret + mod) % mod;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int k; cin >> num >> k;
    for (int i = 0; i < num; i++)
        cin >> arr[i].first >> arr[i].second;
    initLag();
    cout << lagrange(k) << '\n';
    return 0;
}