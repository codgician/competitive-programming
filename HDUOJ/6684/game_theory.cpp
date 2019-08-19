#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int caseNum; cin >> caseNum;
    while (caseNum--) {
        string str; cin >> str;
        int which = 0, len = str.size();
        while (true) {
            if (which == 0) {
                int pt = 0;
                while (pt < len && str[pt] == 'y')
                    pt++;
                if (pt >= len || str[pt] != 'z')
                    break;
                str[pt] = 'a';
            } else {
                bool flag = false;
                for (auto & ch : str) {
                    if (ch != 'y' && ch != 'z') {
                        ch++; flag = true;
                        break;
                    }
                }
                if (!flag)
                    break;
            }
            which ^= 1;
        }
        cout << str << '\n';
    }
    return 0;
}