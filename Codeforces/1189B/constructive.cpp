#include <bits/stdc++.h>
using namespace std;

#define SIZE 100010

int arr[SIZE], ans[SIZE];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int len; cin >> len;
    for (int i = 0; i < len; i++)
        cin >> arr[i];
    sort(arr + 0, arr + len);

    if (arr[len - 3] + arr[len - 2] <= arr[len - 1]) {
        cout << "NO\n";
        return 0;
    }

    cout << "YES\n";
    cout << arr[len - 2] << ' ' << arr[len - 1] << ' ' << arr[len - 3];
    for (int i = 0; i < len - 3; i++)
        cout << ' ' << arr[i];
    cout << '\n';

    return 0;
}