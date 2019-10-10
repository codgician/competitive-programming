#include <bits/stdc++.h>
using namespace std;

int pre[2] = {-1, -1};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    
    string str; int len; cin >> len >> str;
    long long int ans = 0; pre[str[0] - 'A'] = 0;
    bool allSame = true;
    for (int i = 1; i < len; i++) {
        const auto & ch = str[i];
        if (str[i - 1] == ch) {
            ans += i - 1 + allSame;
        } else {
            allSame = false;
            ans += pre[ch - 'A'] + 1;
        }
        pre[ch - 'A'] = i;
    }

    cout << ans << '\n';
    return 0;
}