#include <bits/stdc++.h>
using namespace std;

#define SIZE 200020

const int mod = 1e9 + 7;

long long int factorials[SIZE], invFactorials[SIZE];

long long int fastPow(long long int a, long long int n, long long int mod) {
    long long int ret = 1; a %= mod;
    while (n > 0) {
        if (n & 1)
            ret = (ret * a) % mod;
        a = (a * a) % mod; n >>= 1;
    }
    return ret;
}

void initFactorial() {
    factorials[0] = 1;
    for (int i = 1; i < SIZE; i++)
        factorials[i] = i * factorials[i - 1] % mod; 
}

void initInvFactorial() {
    invFactorials[SIZE - 1] = fastPow(factorials[SIZE - 1], mod - 2, mod);
    for (int i = SIZE - 2; i >= 0; i--) {
        invFactorials[i] = invFactorials[i + 1] * (i + 1) % mod;
    }
}

long long int comb(int n, int m) {
    if (m > n)
        return 0;
    return factorials[n] * invFactorials[m] % mod * invFactorials[n - m] % mod;
}

pair<int, int> arr[SIZE];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    initFactorial(); initInvFactorial();
    int caseNum; cin >> caseNum;
    while (caseNum--) {
        int len; cin >> len;
        int siz = len << 1;
        for (int i = 0; i < siz; i++) {
            cin >> arr[i].first;
            arr[i].second = 1;
        }
        sort(arr + 0, arr + siz);

        int lenPt = 0;
        for (int i = 1; i < siz; i++) {
            if (arr[i].first == arr[lenPt].first)
                arr[lenPt].second += arr[i].second;
            else
                arr[++lenPt] = arr[i];
        }
        siz = ++lenPt;

        long long int ret = (arr[0].second & 1) ? (comb(arr[0].second, arr[0].second >> 1) * 2) : comb(arr[0].second, arr[0].second >> 1);
        int pfx = arr[0].second & 1;
        for (int i = 1; i < siz; i++) {
            if (arr[i].second & 1) {
                ret = ret * (comb(arr[i].second, arr[i].second >> 1) * ((pfx & 1) ? 1 : 2)) % mod;
            } else {
                ret = ret * (comb(arr[i].second, arr[i].second >> 1) + (pfx & 1) * comb(arr[i].second, (arr[i].second >> 1) + 1)) % mod;
            }
            pfx ^= arr[i].second & 1;
        }
        cout << ret << '\n';
    }

    return 0;
}