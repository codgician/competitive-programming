#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int len, k; cin >> len >> k;
    string str; cin >> str;

    if (k == 0) {
        cout << str << '\n';
        return 0;
    }

    if (len == 1) {
        cout << '0' << '\n';
        return 0;
    }

    if (str[0] != '1')
        str[0] = '1', k--;
    int cntPt = 1;
    while (k > 0 && cntPt < len) {
        if (str[cntPt] != '0')
            str[cntPt] = '0', k--;
        cntPt++;
    }

    cout << str << '\n';

    return 0;
}