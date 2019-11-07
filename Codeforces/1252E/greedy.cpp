#include <bits/stdc++.h>
using namespace std;
 
#define SIZE 100010
 
int arr[SIZE], ans[SIZE];
pair<int, int> rng[SIZE];
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
 
    int len, l, r, k; cin >> len >> l >> r >> k;
    for (int i = 0; i < len; i++)
        cin >> arr[i];
    rng[len - 1] = make_pair(l, r);
    for (int i = len - 2; i >= 0; i--) {
        rng[i] = rng[i + 1];
        if (arr[i] < arr[i + 1]) {
            rng[i].first = max(l, rng[i].first - k);
            rng[i].second -= 1;
        } else if (arr[i] > arr[i + 1]) {
            rng[i].first += 1;
            rng[i].second = min(r, rng[i].second + k);
        }
 
        if (rng[i].first > rng[i].second) {
            cout << -1 << '\n';
            return 0;
        }
    }
 
    ans[0] = rng[0].first;
    for (int i = 1; i < len; i++) {
        if (arr[i] > arr[i - 1]) {
            ans[i] = max(ans[i - 1] + 1, rng[i].first);
        } else if (arr[i] < arr[i - 1]) {
            ans[i] = max(ans[i - 1] - k, rng[i].first);
        } else {
            ans[i] = ans[i - 1];
        }
    }
 
    for (int i = 0; i < len; i++)
        cout << ans[i] << ' ';
    cout << '\n';
    return 0;
}