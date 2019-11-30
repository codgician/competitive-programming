#include <bits/stdc++.h>
using namespace std;

int arr[3];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int caseNum; cin >> caseNum;
    while (caseNum--) {
        for (int i = 0; i < 3; i++)
            cin >> arr[i];
        sort(arr + 0, arr + 3);

        int ret = min(arr[2], arr[0] + arr[1]) + max(0, min(arr[0], (arr[0] + arr[1] - arr[2]) >> 1));
        cout << ret << '\n';
    }

    return 0;
}