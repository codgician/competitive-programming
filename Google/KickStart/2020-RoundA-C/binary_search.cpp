#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int caseNum; cin >> caseNum;
    for (int t = 1; t <= caseNum; t++) {
        int len, opt; cin >> len >> opt;
        int pre; cin >> pre; vector<int> v;
        int leftPt = 1, rightPt = 1, ret = -1;
        for (int i = 1; i < len; i++) {
            int cnt; cin >> cnt;
            v.push_back(cnt - pre); pre = cnt;
            rightPt = max(rightPt, v.back() + 1);
        }

        while (leftPt <= rightPt) {
            int midPt = (leftPt + rightPt) >> 1;

            const auto check = [opt, v](int lim) {
                int cnt = 0;
                for (const auto & i : v) {
                    if (i <= lim)
                        continue;
                    cnt += i / lim - (i % lim == 0);
                    if (cnt > opt)
                        return false;
                }
                return true;
            };

            if (check(midPt)) {
                rightPt = midPt - 1, ret = midPt;
            } else {
                leftPt = midPt + 1;
            }
        }
    
        cout << "Case #" << t << ": " << ret << '\n';
    }
    return 0;
}