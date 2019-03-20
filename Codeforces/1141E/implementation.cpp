#include <bits/stdc++.h>
using namespace std;

#define SIZE 200010

long long int arr[SIZE];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    long long int tot, peak = 0;
    int len;
    cin >> tot >> len;
    for (int i = 0; i < len; i++)
        cin >> arr[i];
    if (arr[0] + tot <= 0) {
        cout << 1 << endl;
        return 0;
    }

    for (int i = 1; i < len; i++) {
        arr[i] += arr[i - 1];
        peak = min(peak, arr[i - 1]);
        if (arr[i] + tot <= 0) {
            cout << i + 1 << endl;
            return 0;
        }
    }

    if (peak >= 0 || arr[len - 1] >= 0) {
        cout << -1 << endl;
        return 0;
    }

    long long int cycleNum = max(0ll, (tot + peak) / abs(arr[len - 1]));
    long long int ans = cycleNum * len;
    tot += cycleNum * arr[len - 1];

    while (tot > 0) {
        for (int i = 0; i < len; i++) {
            if (tot + arr[i] <= 0) {
                cout << ans + i + 1 << endl;
                return 0;
            }
        }
        ans += len;
        tot += arr[len - 1];
    }

    return 0;
}