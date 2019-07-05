#include <bits/stdc++.h>
using namespace std;

#define SIZE 300010

long long int arr[SIZE];
int len, mod, k;

map<long long int, int> mp;

long long int combN2(long long int n) {
    return 1ll * n * (n - 1) / 2;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    cin >> len >> mod >> k;
    for (int i = 0; i < len; i++)
        cin >> arr[i];
    for (int i = 0; i < len; i++)
        arr[i] = arr[i] * (arr[i] * arr[i] % mod * arr[i] % mod - k + mod) % mod;
    sort(arr + 0, arr + len);

    for (int i = 0; i < len; i++)
        mp[arr[i]]++;
    long long int ans = 0;
    for (auto p : mp)
        if (p.second > 1)
            ans += combN2(p.second);
    cout << ans << '\n';

    return 0;
}