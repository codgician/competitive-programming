#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int caseNum; cin >> caseNum;
    while (caseNum--) {
        int len, lim, fstPt, sndPt;
        cin >> len >> lim >> fstPt >> sndPt;
        if (fstPt > sndPt)
            swap(fstPt, sndPt);
        int ub = fstPt - 1 + len - sndPt;
        if (lim <= ub) {
            cout << sndPt - fstPt + lim << '\n';
        } else {
            cout << len - 1 << '\n';
        }
    }

    return 0;
}