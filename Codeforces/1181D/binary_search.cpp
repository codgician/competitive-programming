#include <bits/stdc++.h>
using namespace std;

#define SIZE 500010

long long int arr[SIZE];
int num[SIZE];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int befNum, cityNum, qNum;
    cin >> befNum >> cityNum >> qNum;
    memset(num, 0, sizeof(num));
    for (int i = 0; i < befNum; i++) {
        int cnt; cin >> cnt; cnt--;
        long long int origPos = 1ll * num[cnt] * cityNum + cnt;
        arr[i] = origPos;
        num[cnt]++;
    }

    sort(arr + 0, arr + befNum);

    for (int i = 0; i < befNum; i++)
        arr[i] -= i;

    while (qNum--) {
        long long int pos; cin >> pos;
        if (pos - befNum <= arr[befNum - 1]) {
            pos -= befNum;
            pos += lower_bound(arr + 0, arr + befNum, pos) - arr;
        }
        cout << (pos - 1) % cityNum + 1 << '\n';
    }

    return 0;
}