#include <bits/stdc++.h>
using namespace std;

#define SIZE 300010

long long int arr[SIZE];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int lim;
    cin >> lim;
    long long int ans = 0;
    for (int i = 0; i < lim; i++)
        cin >> arr[i];

    queue<int> q;
    for (int i = 0; i < lim; i++) {
        if (arr[i] == 0)
            continue;
        q.push(i);

        while (!q.empty()) {
            int fnt = q.front();
            if (arr[fnt] == 0) {
                q.pop();
                continue;
            }
            if (fnt == i) {
                ans += arr[i] / 3;
                arr[i] %= 3;
            } else {
                long long int take = min(arr[i] >> 1, arr[fnt]);
                arr[fnt] -= take, arr[i] -= (take << 1);
                ans += take;
            }
            if (arr[fnt] == 0)
                q.pop();
            else
                break;
        }
    }

    for (int i = 0; i < lim; i++) {
        ans += arr[i] / 3;
        arr[i] %= 3;
    }

    cout << ans << endl;
    return 0;
}