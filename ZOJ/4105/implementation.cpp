#include <bits/stdc++.h>
using namespace std;

bool isVowel(char ch) {
    return ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u' || ch == 'y';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int caseNum;
    cin >> caseNum;
    while (caseNum--) {
        string str;
        cin >> str;
        cout << str[0];
        for (int i = 1; i < (int)str.size(); i++)
            if (!isVowel(str[i]))
                cout << str[i];
        cout << '\n';
    }

    return 0;
}