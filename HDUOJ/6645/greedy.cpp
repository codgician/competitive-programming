#include <bits/stdc++.h>
using namespace std;

#define SIZE 100010

int arr[SIZE];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int caseNum; cin >> caseNum;
    while (caseNum--) {
        int len; cin >> len;
        for (int i = 0; i < len; i++)
            cin >> arr[i];
        sort(arr + 0, arr + len);

        long long int ans[2] = {0, 0};
        for (int i = 0; i < len; i++)
            ans[i & 1] += arr[i];
        if (ans[0] < ans[1])
            swap(ans[0], ans[1]);
        cout << ans[0] << ' ' << ans[1] << '\n';
    }

    return 0;
}