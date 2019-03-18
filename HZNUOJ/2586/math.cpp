#include <bits/stdc++.h>
using namespace std;

#define SIZE 100010

pair<long double, int> arr[SIZE];
int ans[SIZE];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int len;
    while (cin >> len) {
        for (int i = 0; i < len; i++) {
            cin >> arr[i].first;
            arr[i].first /= log2(arr[i].first);
            arr[i].second = i;
        }
        sort(arr + 0, arr + len, greater<pair<long double, int>>());
        
        int cnt = 0;
        for (int i = 0; i < len; i++) {
            if (i > 0 && arr[i - 1].first != arr[i].first) {
                cnt = i;
            }
            ans[arr[i].second] = cnt;
        }
        for (int i = 0; i < len; i++) {
            cout << ans[i] << (i < len - 1 ? ' ' : '\n');
        }
    }
    
    return 0;
}