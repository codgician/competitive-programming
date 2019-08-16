#include <bits/stdc++.h>
using namespace std;
 
int getLen(int num) {
    int ret = 0;
    while (num > 0) {
        ret++; num /= 10;
    }
    return ret;
}
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
 
    int num, p; cin >> num >> p;
    int len = getLen(p);
    if (num >= len) {
        cout << p;
        for (int i = 0; i < num - len; i++)
            cout << 0;
        cout << '\n';
    } else {
        cout << "T_T\n";
    }
 
    return 0;
}