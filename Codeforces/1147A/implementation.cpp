#include <bits/stdc++.h>
using namespace std;

#define SIZE 100010

vector<int> vec[SIZE];
int arr[SIZE];
bool vis[SIZE];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    memset(vis, false, sizeof(vis));
    int len, num;
    cin >> len >> num;
    for (int i = 0; i < num; i++) {
        cin >> arr[i];
        arr[i]--;
        vec[arr[i]].push_back(i);
        vis[arr[i]] = true;
    }

    long long int ans = 0;
    for (int i = 0; i < len; i++) {
        if (vis[i]) {
            int cntPos = vec[i].front();
            if (i > 0) {
                auto it = lower_bound(vec[i - 1].begin(), vec[i - 1].end(), cntPos);
                if (it == vec[i - 1].end())
                    ans++;
            }
            if (i < len - 1) {
                auto it = lower_bound(vec[i + 1].begin(), vec[i + 1].end(), cntPos);
                if (it == vec[i + 1].end())
                    ans++;
            }
        } else {
            for (int j = i + 1; j <= len; j++) {
                if (vis[j] || len == j) {
                    int cntLen = j - i;
                    ans += 3ll * cntLen;
                    ans -= (i == 0) + (j == len);
                    i = j - 1;
                    break;
                }
            }
        }
    }

    cout << ans << '\n';
    return 0;
}