#include <bits/stdc++.h>
using namespace std;

#define SIZE 200010

int arr[SIZE];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int len, lim;
    cin >> len >> lim;
    for (int i = 0; i < len; i++)
        cin >> arr[i];
    sort(arr + 0, arr + len);

    int leftPt = 0, rightPt = (len + 1) >> 1;
    int ans = 0;
    while (rightPt < len && leftPt >= 0) {
        if (arr[rightPt] - arr[leftPt] >= lim) {
            ans++;
            leftPt++; rightPt++;
        } else {
            rightPt++;
        }
    }

    cout << ans << '\n';
    return 0;
}