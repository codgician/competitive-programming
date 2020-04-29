#include <bits/stdc++.h>
using namespace std;

#define SIZE 100010

int arr[SIZE];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int caseNum; cin >> caseNum;
    for (int t = 1; t <= caseNum; t++) {
        int len, bud; cin >> len >> bud;
        for (int i = 0; i < len; i++)
            cin >> arr[i];
        sort(arr + 0, arr + len);
        
        int ans = 0, cnt = 0;
        for (int i = 0; i < len && cnt + arr[i] <= bud; i++)
            ans++, cnt += arr[i];
        cout << "Case #" << t << ": " << ans << '\n';
    }

    return 0;
}