#include <bits/stdc++.h>
using namespace std;

#define SIZE 3010
#define INV_SIZE 500010

const long long int mod = 1e9 + 7;

pair<int, int> arr[SIZE];
long long int delta[SIZE][SIZE], inv[INV_SIZE];

void initInv() {
    inv[1] = 1;
    for (int i = 2; i < INV_SIZE; i++)
        inv[i] = (mod - mod / i) * inv[mod % i] % mod;
}

long long int getInv(int num) {
    return (num < 0 ? -inv[-num] : inv[num]);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    initInv();
    int num;
    while (cin >> num) {
        for (int i = 0; i < num; i++)
            cin >> arr[i].first >> arr[i].second;
        for (int i = 0; i < num; i++)
            delta[i][i] = arr[i].second;
        for (int d = 1; d < num; d++)
            for (int i = 0; i + d < num; i++)
                delta[i][i + d] = (delta[i][i + d - 1] - delta[i + 1][i + d]) * getInv(arr[i].first - arr[i + d].first) % mod;

        int qNum; cin >> qNum;
        while (qNum--) {
            int l, r, x; cin >> l >> r >> x; l--; r--;
            long long int ans = 0, prod = 1;
            for (int i = l; i <= r; i++) {
                ans = (ans + prod * delta[l][i]) % mod;
                prod = prod * (x - arr[i].second) % mod;
            }
            cout << (ans + mod) % mod << '\n';
        }
    }

    return 0;
}