#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int len; string str; cin >> len >> str;
    for (char ch = 'z'; ch >= 'a'; ch--) {
        const auto erase = [ch, &str]() {
            for (int i = 0; i < (int)str.size(); i++) {
                if (str[i] != ch)
                    continue;
                const auto check = [i, str]() {
                    if (i == 0)
                        return str[i + 1] == str[i] - 1;
                    if (i == (int)str.size() - 1)
                        return str[i - 1] == str[i] - 1;
                    return str[i + 1] == str[i] - 1 || str[i - 1] == str[i] - 1;
                };
                if (check()) {
                    str.erase(i, 1);
                    return true;
                }
            }
            return false;
        };
        while (erase());
    }

    cout << len - (int)str.size() << '\n';
    return 0;
}