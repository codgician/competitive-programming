#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int caseNum;
    cin >> caseNum;
    while (caseNum--) {
        long long int num;
        cin >> num;
        if (num == 1) {
            cout << "8 9\n";
        } else {
            cout << num * 2 << " " << num * 3 << '\n';
        }
    }

    return 0;
}