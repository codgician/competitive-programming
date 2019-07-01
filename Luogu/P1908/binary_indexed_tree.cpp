#include <bits/stdc++.h>
using namespace std;

#define SIZE 500010

int arr[SIZE], dsc[SIZE], bit[SIZE];

int lowbit(int n) {
    return n & -n;
}

void add(int pos, int val) {
    pos++;
    for (int i = pos; i < SIZE; i += lowbit(i))
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

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    memset(bit, 0, sizeof(bit));

    long long int ans = 0;
    int len; cin >> len;
    for (int i = 0; i < len; i++) {
        cin >> arr[i];
        dsc[i] = arr[i];
    }

    // Discretization
    sort(dsc + 0, dsc + len);
    int dscLen = unique(dsc + 0, dsc + len) - dsc;
    for (int i = 0; i < len; i++)
        arr[i] = lower_bound(dsc + 0, dsc + dscLen, arr[i]) - dsc;

    for (int i = 0; i < len; i++) {
        ans += rangeSum(arr[i] + 1, SIZE - 1);
        add(arr[i], 1);
    }

    cout << ans << '\n';
    return 0;
}