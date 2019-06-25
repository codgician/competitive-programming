#include <bits/stdc++.h>
using namespace std;

#define SIZE 110

int arr[SIZE], ans, len;

bool check() {
    ans = 0;
    for (int i = 1; i < len; i++) {
        if (arr[i] == 1) {
            // circle
            if (arr[i - 1] == 1)
                return false;
            ans += arr[i - 1] + 1;
        } else {
            if (arr[i - 1] != 1)
                return false;
            ans += arr[i] + 1;
            if (i > 1 && arr[i] == 2 && arr[i - 1] == 1 && arr[i - 2] == 3)
                ans--;
        }
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> len;
    for (int i = 0; i < len; i++)
        cin >> arr[i];

    if (check())
        cout << "Finite\n" << ans << '\n';
    else
        cout << "Infinite\n";

    return 0;
}