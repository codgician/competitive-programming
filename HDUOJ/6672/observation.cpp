#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int caseNum; cin >> caseNum;
    while (caseNum--) {
        long long int num; cin >> num;
        int rem = num % 6;
        if (rem == 0 || rem == 2) {
            cout << (num >> 1) << '\n';
        } else if (rem == 1) {
            cout << num - ((num / 6) << 1) << '\n';
        } else if (rem == 3 || rem == 5) {
            cout << (num / 6) << '\n';
        } else {
            cout << num - 1 << '\n';
        }
    }

    return 0;
}