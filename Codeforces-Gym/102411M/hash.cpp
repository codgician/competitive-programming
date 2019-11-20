#include <bits/stdc++.h>
using namespace std;
 
#define SIZE 2010
 
int arr[SIZE];
unordered_map<int, int> mp;
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
 
    int caseNum; cin >> caseNum;
    while (caseNum--) {
        int len; cin >> len; mp.clear();
        for (int i = 0; i < len; i++)
            cin >> arr[i], mp[arr[i]]++;
 
        int ans = 0;
        for (int j = 0; j < len; j++) {
            mp[arr[j]]--;
            for (int i = 0; i < j; i++)
                ans += mp[2 * arr[j] - arr[i]];
        }
        cout << ans << '\n';
    }
 
    return 0;
}