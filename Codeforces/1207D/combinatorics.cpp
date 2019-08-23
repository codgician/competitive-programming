#include <bits/stdc++.h>
using namespace std;
 
#define SIZE 300010
const int mod = 998244353;
 
long long int factorials[SIZE];
map<int, int> mp1, mp2;
map<pair<int, int>, int> mp3;
 
void initFactorials() {
    factorials[0] = 1;
    for (int i = 1; i < SIZE; i++)
        factorials[i] = factorials[i - 1] * i % mod;
}
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    initFactorials();
    int len; cin >> len;
    for (int i = 0; i < len; i++) {
        pair<int, int> p; cin >> p.first >> p.second;
        mp1[p.first]++; mp2[p.second]++; mp3[p]++;
    }
 
    long long int ans = factorials[len], ans1 = 1;
    for (auto & p : mp1)
        ans1 = ans1 * factorials[p.second] % mod;
    ans = (ans - ans1 + mod) % mod; ans1 = 1;
    for (auto & p : mp2)
        ans1 = ans1 * factorials[p.second] % mod;
    ans = (ans - ans1 + mod) % mod; ans1 = factorials[mp3.begin() -> second];
    for (auto it = next(mp3.begin()); it != mp3.end(); ++it) {
        if (it -> first.second < prev(it) -> first.second) {
            ans1 = 0; break;
        }
        ans1 = ans1 * factorials[it -> second] % mod;
    }
 
    cout << (ans + ans1) % mod << '\n';
    return 0;
}