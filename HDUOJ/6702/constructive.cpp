#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int caseNum; cin >> caseNum;
    while (caseNum--) {
        unsigned int fst, snd, ans = 0;
        cin >> fst >> snd;
        for (int i = 31; i >= 0; i--) {
            unsigned int fstBt = (fst & (1u << i)) ? 1 : 0, sndBt = (snd & (1u << i)) ? 1 : 0;
            ans += (fstBt & sndBt) << i;
        }
        cout << (ans == 0 ? 1 : ans) << '\n';
    }

    return 0;
}