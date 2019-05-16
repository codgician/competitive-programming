#include <bits/stdc++.h>
using namespace std;

#define SIZE 500010
const int mod = 1e9 + 7;

int arr[SIZE], dsc[SIZE], len;
long long int bit[SIZE];

int lowbit(int n) {
    return n & -n;
}

void add(int pos, long long int val) {
    pos++;
    for (int i = pos; i <= len; i += lowbit(i))
        bit[i] += val;
}

long long int prefixSum(int pos) {
    long long int ret = 0; pos++;
    for (int i = pos; i > 0; i -= lowbit(i))
        ret += bit[i];
    return ret;
}

long long int rangeSum(int qLeftPt, int qRightPt) {
    return prefixSum(qRightPt) - prefixSum(qLeftPt - 1);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    memset(bit, 0, sizeof(bit));
    cin >> len;
    for (int i = 0; i < len; i++) {
        cin >> arr[i];
        dsc[i] = arr[i];
    }

    long long int ans = 0;
    sort(dsc + 0, dsc + len);
    for (int i = 0; i < len; i++) {
        arr[i] = lower_bound(dsc + 0, dsc + len, arr[i]) - dsc;
        ans = (ans + 1ll * dsc[arr[i]] * (i + 1) % mod * (len - i) % mod) % mod;
        ans = (ans + 1ll * rangeSum(arr[i], len - 1) % mod * (len - i) % mod) % mod;
        add(arr[i], 1ll * (i + 1) * dsc[arr[i]] % mod);
    }

    memset(bit, 0, sizeof(bit));
    for (int i = len - 1; i >= 0; i--) {
        ans = (ans + 1ll * rangeSum(arr[i], len - 1) % mod * (i + 1) % mod) % mod;
        add(arr[i], 1ll * (len - i) * dsc[arr[i]] % mod);
    }

    cout << ans << '\n';
    return 0;
}
