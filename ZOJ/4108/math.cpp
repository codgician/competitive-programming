#include <bits/stdc++.h>
using namespace std;

int mod3(const string & str) {
    int ret = 0;
    for (auto ch : str)
        ret = (ret + ch - '0') % 3;
    return ret;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int caseNum;
    cin >> caseNum;
    while (caseNum--) {
        string fst, snd;
        cin >> fst >> snd;
        int qLeftPt = mod3(fst), qRightPt = mod3(snd);
        qLeftPt = (qLeftPt - 1 + 3) % 3;

        if ((qLeftPt == 1) == (qRightPt == 1))
            cout << "0\n";
        else
            cout << "1\n";
    }
    return 0;
}