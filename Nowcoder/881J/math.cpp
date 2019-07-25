#include <bits/stdc++.h>
using namespace std;
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
 
    long long int x, a, y, b;
    while (cin >> x >> a >> y >> b) {
        __int128 fst = (__int128)x * b, snd = (__int128)y * a;
        if (fst == snd)
            cout << "=\n";
        else if (fst < snd)
            cout << "<\n";
        else
            cout << ">\n";
    }
 
    return 0;
}