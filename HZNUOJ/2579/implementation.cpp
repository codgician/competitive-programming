#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    
    string str;
    while (getline(cin, str)) {
        int len = str.size();
        if (str[len - 1] == '.') 
            str[len - 1] = '!';
        cout << str << endl;
    }

    return 0;
}