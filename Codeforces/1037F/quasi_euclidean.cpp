#include <bits/stdc++.h>
using namespace std;

#define SIZE 1000010

const long long int mod = 1e9 + 7;

long long int arr[SIZE];
int leftPos[SIZE], rightPos[SIZE];

stack<pair<long long int, int> > mstk;

long long int quasiEuclidean(long long int a, long long int b, long long int c, long long int n) {
    if (a == 0) {
        return (n + 1) * (b / c) % mod;
    }
    if (a >= c || b >= c) {
        long long int tmp = ((n & 1) ? ((n + 1) >> 1) * n : (n >> 1) * (n + 1)) % mod;
        return ((a / c) * tmp % mod + (b / c) * (n + 1) % mod + quasiEuclidean(a % c, b % c, c, n)) % mod;
    }
    long long int m = (a * n + b) / c;
    return (n * m % mod - quasiEuclidean(c, c - b - 1, a, m - 1) + mod) % mod;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int len, k;
    cin >> len >> k;
    for (int i = 0; i < len; i++)
        cin >> arr[i];
    leftPos[0] = 0;
    mstk.push(make_pair(arr[0], 0));
    for (int i = 1; i < len; i++) {
        while (!mstk.empty() && mstk.top().first <= arr[i])
            mstk.pop();
        if (mstk.empty())
            leftPos[i] = 0;
        else
            leftPos[i] = mstk.top().second + 1;
        mstk.push(make_pair(arr[i], i));
    }

    mstk = stack<pair<long long int, int> >();
    rightPos[len - 1] = len - 1;
    mstk.push(make_pair(arr[len - 1], len - 1));
    for (int i = len - 2; i >= 0; i--) {
        while (!mstk.empty() && mstk.top().first < arr[i])
            mstk.pop();
        if (mstk.empty())
            rightPos[i] = len - 1;
        else
            rightPos[i] = mstk.top().second - 1;
        mstk.push(make_pair(arr[i], i));
    }

    long long int ans = 0;
    for (long long int i = 0; i < len; i++) {
        long long int l = leftPos[i], r = rightPos[i];
        ans += (quasiEuclidean(1, r - i, k - 1, i - l) - quasiEuclidean(1, 0, k - 1, i - l - 1) + mod) % mod * arr[i] % mod;
        ans %= mod;
    }

    cout << ans << endl;

     return 0;
}