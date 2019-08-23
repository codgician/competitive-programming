#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int caseNum; cin >> caseNum;
    while (caseNum--) {
        int buns, beef, chicken, h, c, ans = 0; cin >> buns >> beef >> chicken >> h >> c;
        for (int i = 0; i <= beef; i++)
            for (int j = 0; j <= chicken; j++)
                if (((i + j) << 1) <= buns)
                    ans = max(ans, i * h + j * c);
        cout << ans << '\n';
    }

    return 0;
}