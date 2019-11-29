#include <bits/stdc++.h>
using namespace std;
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
 
    int caseNum; cin >> caseNum;
    while (caseNum--) {
        long long int fst, snd; cin >> fst >> snd;
        long long int delta = abs(fst - snd);
        long long int ans = delta / 5; delta %= 5;
        ans += delta / 2; delta %= 2; ans += delta;
        cout << ans << '\n';
    }
 
    return 0;
}