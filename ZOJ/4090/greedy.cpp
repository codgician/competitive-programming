#include <bits/stdc++.h>
using namespace std;

#define SIZE 100010

pair<int, bool> fstArr[SIZE], sndArr[SIZE];
set<int> shortSt, highSt;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int caseNum;
    cin >> caseNum;
    while (caseNum--) {
        shortSt.clear(); highSt.clear();
        int fstNum, sndNum;
        cin >> fstNum >> sndNum;
        for (int i = 0; i < fstNum; i++)
            cin >> fstArr[i].first;
        for (int i = 0; i < sndNum; i++)
            cin >> sndArr[i].first;

        for (int i = 0; i < fstNum; i++)
            cin >> fstArr[i].second;
        for (int i = 0; i < sndNum; i++) {
            cin >> sndArr[i].second;
            if (sndArr[i].second == 0)
                shortSt.insert(sndArr[i].first);
            else
                highSt.insert(sndArr[i].first);
        }

        int ans = 0;
        for (int i = 0; i < fstNum; i++) {
            if (fstArr[i].second == 0) {
                // Prefers lady that prefers higher gentleman
                if (highSt.empty())
                    continue;

                auto it = highSt.lower_bound(fstArr[i].first);
                if (it == highSt.begin()) {
                    continue;
                }

                it = prev(it);
                highSt.erase(it);
                ans++;
            } else {
                // Otherwise
                if (shortSt.empty())
                    continue;

                auto it = shortSt.lower_bound(fstArr[i].first);
                if (it == shortSt.end()) {
                    continue;
                }

                shortSt.erase(it);
                ans++;
            }
        }

        cout << ans << endl;
    }

    return 0;
}