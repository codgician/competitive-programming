#include <bits/stdc++.h>
using namespace std;

#define SIZE 1010

long long int arr[SIZE];

int init() {
    arr[1] = 1, arr[2] = 2; int i;
    for (i = 3; arr[i - 1] <= 1e18; i++) {
        arr[i] = arr[i - 1] + arr[i - 1] / 2;
    }
    return i;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int arrPt = init();
    long long int num; cin >> num;
    int ans = lower_bound(arr + 1, arr + arrPt, num) - arr;
    ans += (arr[ans] == num);
    cout << ans << endl;
    return 0;
}