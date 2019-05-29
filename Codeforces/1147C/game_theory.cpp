#include <bits/stdc++.h>
using namespace std;

map<int, int> mp;
int len;

bool check() {
    return (mp.begin() -> second) <= (len >> 1);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> len;
    for (int i = 0; i < len; i++) {
        int cnt;
        cin >> cnt;
        mp[cnt]++;
    }

    cout << (check() ? "Alice\n" : "Bob\n");
    return 0;
}