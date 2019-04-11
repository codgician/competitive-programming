#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int caseNum;
    cin >> caseNum;
    while (caseNum--) {
        int num;
        cin >> num;
        int fst = 0, snd = 0;
        for (int i = 0; i < num; i++) {
            int cnt;
            cin >> cnt;
            if (cnt == 1) {
                fst++;
            } else if (cnt == 2) {
                snd++;
            } else if (cnt == 3) {
                fst++, snd++;
            } else {
                fst--, snd--;
            }
        }
        if (fst > snd) {
            cout << "Kobayashi" << endl;
        } else if (fst < snd) {
            cout << "Tohru" << endl;
        } else {
            cout << "Draw" << endl;
        }
    }

    return 0;
}