#include <bits/stdc++.h>
using namespace std;

int arr[20][20], num[20];

const int mod = 998244353;

int getLen(int num) {
    int ret = 0;
    while (num > 0) {
        ret++; num /= 10;
    }
    return ret;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int len; cin >> len;
    for (int i = 0; i < len; i++) {
        int cnt; cin >> cnt;
        int cntLen = getLen(cnt), pt = 0;
        num[cntLen]++;
        while (cnt > 0) {
            arr[cntLen][pt++] += cnt % 10;
            cnt /= 10;
        }
    }

    for (int i = 2; i <= 10; i++)
        num[i] += num[i - 1];

    long long int ans = 0;
    for (int i = 1; i <= 10; i++) {
        // Inside each block
        int cntNum = num[10] - num[i - 1];
        long long int fac = 1;
        for (int j = 0; j < i; j++) {
            ans = (ans + arr[i][j] * fac % mod * cntNum % mod) % mod;
            ans = (ans + arr[i][j] * fac % mod * 10 % mod * cntNum % mod) % mod;
            fac = fac * 100 % mod;
        }

        // Contributions towards previous blocks
        for (int j = 1; j < i; j++) {
            long long int qaqNum = num[j] - num[j - 1];
            for (int t = 0; t < 2; t++) {
                int pt = t, qaqPt = 0; long long int fac = t == 0 ? 1 : 10;
                while (pt < 2 * j - t) {
                    ans = (ans + arr[i][qaqPt++] * fac % mod * qaqNum % mod) % mod;
                    fac = fac * 100 % mod; pt += 2;
                }
                while (pt < i + j) {
                    ans = (ans + arr[i][qaqPt++] * fac % mod * qaqNum % mod) % mod;
                    fac = fac * 10 % mod; pt++;
                }
            } 
        }
    }

    cout << ans << '\n';

    return 0;
}