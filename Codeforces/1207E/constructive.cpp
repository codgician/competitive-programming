#include <bits/stdc++.h>
using namespace std;
 
int main() {
    int fst, snd;
    cout << "? ";
    for (int i = 1; i <= 100; i++)
        cout << i << ' ';
    cout << endl; cin >> fst;
    cout << "? ";
    for (int i = 1; i <= 100; i++)
        cout << (i << 7) << ' ';
    cout << endl; cin >> snd;
    cout << "! " << (fst - fst % 128 + snd % 128) << endl;
 
    return 0;
}