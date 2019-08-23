#include <bits/stdc++.h>
using namespace std;

#define SIZE 510000

const int lim = 710;

long long int arr[SIZE], mp[SIZE];

const auto p2ll = [](long long int x, long long int y) {
    return x * lim + y;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int qNum; cin >> qNum;
    while (qNum--) {
        int op, fst, snd; cin >> op >> fst >> snd;
        if (op == 1) {
            for (int i = 1; i <= lim; i++) {
                int rem = fst % i;
                mp[p2ll(i, rem)] += snd;
            }
            arr[fst] += snd;
        } else {
            long long int ans = 0;
            if (fst > lim) {
                for (int i = snd; i < SIZE; i += fst)
                    ans += arr[i];
            } else {
                ans = mp[p2ll(fst, snd)];
            }
            cout << ans << '\n';
        }
    }

    return 0;
}