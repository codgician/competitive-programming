#include <bits/stdc++.h>
using namespace std;
 
#define SIZE 10
 
bool vis[SIZE];
 
bool check(int n) {
    fill(vis + 0, vis + SIZE, false);
    while (n > 0) {
        int cnt = n % 10; n /= 10;
        if (vis[cnt])
            return false;
        vis[cnt] = true;
    } 
    return true;
}
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
 
    int leftPt, rightPt, ans = -1;
    cin >> leftPt >> rightPt;
    for (int i = leftPt; i <= rightPt; i++) {
        if (check(i)) {
            ans = i; break;
        }
    }
 
    cout << ans << '\n';
    return 0;
}