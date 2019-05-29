#include <bits/stdc++.h>
using namespace std;

#define SIZE 55

int arr[SIZE];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int len, maxHeight, limNum;
    cin >> len >> maxHeight >> limNum;
    for (int i = 0; i < len; i++)
        arr[i] = maxHeight;
    for (int i = 0; i < limNum; i++) {
        int leftPt, rightPt, lim;
        cin >> leftPt >> rightPt >> lim;
        leftPt--; rightPt--;
        for (int i = leftPt; i <= rightPt; i++) {
            arr[i] = min(arr[i], lim);
        }
    }

    int ans = 0;
    for (int i = 0; i < len; i++)
        ans += arr[i] * arr[i];
    cout << ans << '\n';
    return 0;
}