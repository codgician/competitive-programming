#include <bits/stdc++.h>
using namespace std;

#define SIZE 2010

class Item {
public:
    int val, cost;
};

Item arr[SIZE];
vector<int> v[SIZE];
int dp[SIZE];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int caseNum; cin >> caseNum;
    for (int t = 1; t <= caseNum; t++) {
        int n, k, p; cin >> n >> k >> p;
        fill(dp + 0, dp + p + 2, 0);
        for (int i = 0; i < n; i++)
            v[i].clear();
        for (int i = 0; i < n; i++) {
            int sum = 0;
            for (int j = 0; j < k; j++) {
                int cnt; cin >> cnt;
                sum += cnt;
                arr[k * i + j].val = sum;
                arr[k * i + j].cost = j + 1;
                v[i].push_back(k * i + j);
            }
        }

        for (int i = 0; i < n; i++) {
            for (int j = p; j >= 0; j--) {
                for (const auto & k : v[i]) {
                    if (j >= arr[k].cost)
                        dp[j] = max(dp[j], dp[j - arr[k].cost] + arr[k].val);
                }
            }
        }

        cout << "Case #" << t << ": " << dp[p] << '\n';
    }
    return 0;
}