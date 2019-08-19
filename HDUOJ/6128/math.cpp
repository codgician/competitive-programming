#include <bits/stdc++.h>
using namespace std;

unordered_map<long long int, int> mp, mp3;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int caseNum; cin >> caseNum;
    while (caseNum--) {
        mp.clear(); mp3.clear();
        int len; long long int mod; cin >> len >> mod;

        const auto cubic = [mod](long long int num) -> long long int {
            return (__int128)num * num % mod * num % mod; 
        };
        const auto comb2 = [](long long int num) -> long long int {
            return num < 2 ? 0 : ((num & 1) ? num * ((num - 1) >> 1) : (num >> 1) * (num - 1));
        };

        for (int i = 0; i < len; i++) {
            long long int cnt; cin >> cnt;
            if (cnt == 0)
                continue;
            mp[cnt]++; mp3[cubic(cnt)]++;
        }

        long long int ans = 0;
        for (const auto & p : mp3)
            ans += comb2(p.second);
        if (mod != 3)
            for (const auto & p : mp)
                ans -= comb2(p.second);
        cout << ans << '\n';
    }

    return 0;
}