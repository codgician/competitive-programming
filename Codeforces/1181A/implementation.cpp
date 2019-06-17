#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    long long int fst, snd, price;
    cin >> fst >> snd >> price;
    long long int ans = (fst + snd) / price, delta = 0;
    if (fst / price + snd / price < ans)
        delta = price - max(fst % price, snd % price);
    cout << ans << " " << delta << '\n';
    return 0;
}