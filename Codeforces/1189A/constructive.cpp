#include <bits/stdc++.h>
using namespace std;

int arr[2] = {0, 0};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int len; string str;
    cin >> len >> str;
    for (int i = 0; i < len; i++)
        arr[str[i] -'0']++;

    if (arr[0] != arr[1]) {
        cout << "1\n" << str << '\n'; 
    } else {
        char ch = str.back(); str.pop_back();
        cout << "2\n" << str << ' ' << ch << '\n';
    }

    return 0;
}