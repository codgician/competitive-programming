#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int caseNum; cin >> caseNum;
    while (caseNum--) {
        string str; cin >> str;
        int siz = str.size();

        const auto check = [str, siz]() {
            for (int i = 0; i < siz - 1; i++)
                if (str[i] != '?' && str[i] == str[i + 1])
                    return false;
            return true;
        };

        if (!check()) {
            cout << -1 << '\n';
            continue;
        }

        for (int i = 0; i < siz; i++) {
            const auto pick = [str, siz](int pos) -> char {
                if (str[pos] != '?')
                    return str[pos];
                if (pos == 0) {
                    if (siz == 1)
                        return 'a';
                    return (str[1] - 'a' + 1) % 3 + 'a';
                }
                if (pos == siz - 1)
                    return (str[siz - 2] - 'a' + 1) % 3 + 'a';

                for (int i = 0; i < 3; i++)
                    if (i != str[pos - 1] - 'a' && i != str[pos + 1] - 'a')
                        return 'a' + i;
                return 'd';
            };
            str[i] = pick(i);
        }
        
        cout << str << '\n';
    }

    return 0;
}
