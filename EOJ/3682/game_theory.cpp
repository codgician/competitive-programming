#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int row, column, x1, y1, x2, y2;
    cin >> row >> column >> x1 >> y1 >> x2 >> y2;

    int ans = abs(x1 - x2) + abs(y1 - y2);
    if (ans & 1)
        cout << "Lose" << endl;
    else
        cout << "Win" << endl;

    return 0;
}