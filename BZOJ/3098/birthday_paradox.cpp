#include<bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    srand(19260817); int len = 100000;
    cout << len << " 10\n";
    while (len--)
        cout << (char)('a' + rand() % 26);

    return 0;
}