#include <bits/stdc++.h>
using namespace std;

priority_queue<long long int> pq[2];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int caseNum;
    cin >> caseNum;
    while (caseNum--) {
        int num, cap;
        cin >> num >> cap;
        for (int i = 0; i < num; i++) {
            long long int cnt;
            cin >> cnt;
            if (cnt == 0)
                continue;
            pq[cnt > 0].push(llabs(cnt));
        }

        long long int ans = 0;
        ans -= max(pq[0].empty() ? 0ll : pq[0].top(), pq[1].empty() ? 0ll : pq[1].top());

        for (int t = 0; t < 2; t++) {
            while (pq[t].size()) {
                ans += (pq[t].top() << 1);
                for (int i = 0; i < cap && pq[t].size(); i++)
                    pq[t].pop();
            }
        }

        cout << ans << '\n';
    }

    return 0;
}