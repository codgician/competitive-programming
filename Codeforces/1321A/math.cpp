#include <bits/stdc++.h>
using namespace std;

#define SIZE 110

int arr[2][SIZE];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int len; cin >> len;
    for (int t = 0; t < 2; t++)
        for (int i = 0; i < len; i++)   
            cin >> arr[t][i];
    
    long long int sums[2] = {0, 0};
    for (int i = 0; i < len; i++) {
        if (arr[0][i] == arr[1][i])
            continue;
        sums[0] += arr[0][i];
        sums[1] += arr[1][i];
    }

    const auto solve = [](long long int fst, long long int snd) {
        if (snd == 0)
            return -1ll;
        return fst / snd + (fst % snd != 0);
    };
    cout << solve(sums[1] + 1, sums[0]) << '\n';
    return 0;
}