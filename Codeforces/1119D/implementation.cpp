#include <bits/stdc++.h>
using namespace std;

#define SIZE 100010

long long int arr[SIZE];
long long int delta[SIZE], dPfx[SIZE];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int len;
    cin >> len;
    for (int i = 0; i < len; i++)
        cin >> arr[i];
    sort(arr + 0, arr + len);
    len = unique(arr + 0, arr + len) - arr;
    for (int i = 0; i < len - 1; i++)
        delta[i] = arr[i + 1] - arr[i];
    sort(delta + 0, delta + len - 1);
    dPfx[0] = delta[0];
    for (int i = 1; i < len - 1; i++)
        dPfx[i] = dPfx[i - 1] + delta[i];

    int qNum;
    cin >> qNum;
    while (qNum--) {
        long long int qLeftPt, qRightPt;
        cin >> qLeftPt >> qRightPt;
        long long int qLen = qRightPt - qLeftPt + 1, ans = 0;
        int pt = lower_bound(delta + 0, delta + len - 1, qLen) - delta;
        if (pt - 1 >= 0)
            ans += dPfx[pt - 1];
        ans += 1ll * (len - pt) * qLen;
        cout << ans << endl;
    }

    return 0;
}