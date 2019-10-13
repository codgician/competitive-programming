#include <bits/stdc++.h>
using namespace std;
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int zeroNum = 0, oneNum = 0;
    string str; cin >> str; int len = str.size();
    for (const auto & ch : str)
        zeroNum += (ch == '0'), oneNum += (ch == '1');
    
    if (zeroNum > oneNum) {
        for (int i = 0; i < len; i++)
            cout << 1;
        cout << '\n';
        return 0;
    }
    if (oneNum > zeroNum) {
        for (int i = 0; i < len; i++)
            cout << 0;
        cout << '\n';
        return 0;
    }

    cout << ((str[0] - '0') ^ 1);
    for (int i = 1; i < len; i++)
        cout << str[0];
    cout << '\n';

    return 0;
}