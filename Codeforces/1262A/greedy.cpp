#include <bits/stdc++.h>
using namespace std;
 
#define SIZE 100010
 
pair<int, int> arr[SIZE];
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
 
    int caseNum; cin >> caseNum;
    while (caseNum--) {
        int len; cin >> len;
        for (int i = 0; i < len; i++)
            cin >> arr[i].first >> arr[i].second;
        sort(arr + 0, arr + len);
 
        int l = arr[0].first, r = arr[0].second;
        for (int i = 1; i < len; i++) {
            l = max(l, arr[i].first);
            r = min(r, arr[i].second);
        }
        cout << max(0, l - r) << '\n';
    }
 
    return 0;
}