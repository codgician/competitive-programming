#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int caseNum;
    cin >> caseNum;
    while (caseNum--) {
        int num;
        cin >> num;
        while (num % 7 != 0 || num % 4 == 0)
            num++;
        cout << num << '\n';
    }
    return 0;
}

