#include <bits/stdc++.h>
using namespace std;

int arr[4];

bool check() {
    int tot = 0;
    for (int i = 0; i < 4; i++)
        tot += arr[i];
    if (tot & 1)
        return false;
    for (int i = 0; i < 4; i++) {
        if (arr[i] == (tot >> 1))
            return true;
        for (int j = i + 1; j < 4; j++)
            if (arr[i] + arr[j] == (tot >> 1))
                return true;
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    for (int i = 0; i < 4; i++)
        cin >> arr[i];

    cout << (check() ? "YES\n" : "NO\n");
    return 0;
}