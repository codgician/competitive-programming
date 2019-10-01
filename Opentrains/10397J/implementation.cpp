#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    string fst, snd; int ans1 = 0, ans2 = 0;
    cin >> fst >> snd;
    for (int i = 0; i < 6; i++) {
        ans1 += (fst[i] < snd[i]);
        ans2 += (fst[i] > snd[i]);
    }
    cout << ans1 << '\n' << ans2 << '\n';

    return 0;
}