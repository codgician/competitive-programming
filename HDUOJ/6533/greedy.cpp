#include <bits/stdc++.h>
using namespace std;

#define SIZE 200010

long long int arr[SIZE], pfx[SIZE];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int len;
    long long int layer, deg, mod;
    while (cin >> len >> layer >> deg >> mod) {
        pfx[0] = 1;
        for (int i = 1; i <= layer; i++)
            pfx[i] = pfx[i - 1] * deg % mod;
        for (int i = 1; i <= layer; i++)
            pfx[i] = (pfx[i] + pfx[i - 1]) % mod;

        for (int i = 0; i < len; i++)
            cin >> arr[i];
        sort(arr + 0, arr + len);
        long long int ans = 0; int cntPt = 0;
        for (int i = 0; i < layer - 1; i++) {
            long long int cntNum = (pfx[i + 1] - pfx[i] + mod) % mod;
            while (cntNum--)
                ans = (ans + arr[cntPt++] * pfx[layer - 2 - i]) % mod;
        }
        cout << ans << '\n';
    }
    return 0;
}