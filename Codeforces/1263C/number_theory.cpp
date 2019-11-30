#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int caseNum; cin >> caseNum;
    while (caseNum--) {
        int n; vector<int> v; cin >> n;
        for (int l = 1, r; l <= n; l = r + 1) 
            r = n / (n / l), v.push_back(n / l);
        v.push_back(0);
        reverse(v.begin(), v.end());
        cout << v.size() << '\n';
        for (const auto & i : v)
            cout << i << ' ';
        cout << '\n';
    }

    return 0;
}