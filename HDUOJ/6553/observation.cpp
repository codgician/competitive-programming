#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    long long int num;
    while (cin >> num)
        cout << num * (num + 11) / 2 + 7 << '\n';

    return 0;
}