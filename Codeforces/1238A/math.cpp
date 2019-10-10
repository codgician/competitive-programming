#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int caseNum; cin >> caseNum;
    while (caseNum--) {
        long long int x, y; cin >> x >> y;
        cout << (abs(x - y) <= 1 ? "NO" : "YES") << '\n';
    }    
    return 0;
}