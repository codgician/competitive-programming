#include <bits/stdc++.h>
using namespace std;
 
int ceil(int a, int b) {
    return a / b + (a % b > 0);
}
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
 
    int a, b, n; cin >> a >> b >> n;
    cout << ceil((n - a), (b - a)) * 2 - 1 << '\n';
 
    return 0;
}