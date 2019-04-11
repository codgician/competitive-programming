#include <bits/stdc++.h>
using namespace std;

#define SIZE 110

pair<int, int> fstArr[SIZE], sndArr[SIZE];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int caseNum;
    cin >> caseNum;
    while (caseNum--) {
        int dayNum, consNum, fstNum, sndNum;
        cin >> dayNum >> consNum >> fstNum >> sndNum;
        for (int i = 0; i < fstNum; i++)
            cin >> fstArr[i].first >> fstArr[i].second;
        for (int i = 0; i < sndNum; i++)
            cin >> sndArr[i].first >> sndArr[i].second;

        int ans = 0, j = 0;
        for (int i = 0; i < fstNum && j < sndNum; i++) {
            while (j < sndNum && fstArr[i].second >= sndArr[j].first) {
                int len = min(fstArr[i].second, sndArr[j].second) - max(fstArr[i].first, sndArr[j].first) + 1;
                if (len >= consNum)
                    ans += len - consNum + 1;
                if (fstArr[i].second < sndArr[j].second)
                    break;
                j++;
            }
        }
        cout << ans << endl;
    }

    return 0;
}