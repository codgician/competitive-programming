#include <bits/stdc++.h>
using namespace std;

#define SIZE 100010

int pfx[SIZE], pfx[2][SIZE];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int len; cin >> len;
    for (int i = 0; i < len; i++)
        cin >> pfx[i];
    for (int i = 1; i < len; i++)
        pfx[i] += pfx[i - 1];

    int qNum; cin >> qNum;
    while (qNum--) {
        int qLeftPt, qRightPt;
        cin >> qLeftPt >> qRightPt;
        qLeftPt--; qRightPt--;
        int ans = pfx[qRightPt];
        if (qLeftPt > 0)
            ans -= pfx[qLeftPt - 1];
        cout << ans / 10 << '\n';
    }

    return 0;
}