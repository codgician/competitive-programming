#include <bits/stdc++.h>
using namespace std;

#define SIZE 200010

int ans[SIZE];
pair<int, int> arr[SIZE];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int len;
    cin >> len;
    arr[0] = make_pair(1, 0);
    for (int i = 1; i < len; i++) {
        int cnt;
        cin >> cnt;
        arr[i] = make_pair(cnt + arr[i - 1].first, i);
    }

    sort(arr + 0, arr + len);

    for (int i = 0; i < len; i++) {
        if (i > 0 && arr[i - 1].first + 1 != arr[i].first) {
            cout << -1 << endl;
            return 0;
        }
        ans[arr[i].second] = i + 1;
    }
    for (int i = 0; i < len; i++)
        cout << ans[i] << " ";
    cout << endl;

    return 0;
}