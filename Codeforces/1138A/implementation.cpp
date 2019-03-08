#include <bits/stdc++.h>
using namespace std;

#define SIZE 100010

int arr[SIZE];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    memset(arr, 0, sizeof(arr));
    int len, arrPt = 0;
    cin >> len;

    int prev, cnt;
    cin >> prev;
    arr[arrPt] = 1; 
    for (int i = 1; i < len; i++) {
        cin >> cnt;
        if (cnt == prev) {
            arr[arrPt]++;
        } else {
            prev = cnt;
            arr[++arrPt]++;
        }
    }

    int ans = 0;
    for (int i = 0; i < arrPt; i++) {
        ans = max(ans, min(arr[i], arr[i + 1]));
    }
    cout << (ans << 1) << endl;

    return 0;
}