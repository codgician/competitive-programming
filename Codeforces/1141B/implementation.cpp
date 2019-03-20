#include <bits/stdc++.h>
using namespace std;

#define SIZE 400010

int arr[SIZE];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int len;
    cin >> len;
    for (int i = 0; i < len; i++) {
        cin >> arr[i];
    }
    for (int i = 0; i < len; i++) {
        arr[i + len] = arr[i];
    }
    len <<= 1;

    int ans = (arr[0] == 1), cnt = (arr[0] == 1);
    for (int i = 1; i < len; i++) {
        if (arr[i] == 1 && arr[i] == arr[i - 1]) {
            cnt++;
        } else {
            cnt = (arr[i] == 1);
        }
        ans = max(ans, cnt);
    }

    cout << ans << endl;

    return 0;
}