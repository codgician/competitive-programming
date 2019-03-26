#include <bits/stdc++.h>
using namespace std;

#define SIZE 100010

long long int arr[SIZE];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int caseNum;
    cin >> caseNum;
    for (int t = 1; t <= caseNum; t++) {
        int num, sel;
        cin >> num >> sel;
        arr[0] = 0;
        for (int i = 1; i <= num; i++)
            cin >> arr[i];
        sort(arr + 1, arr + num + 1);
        for (int i = 1; i <= num; i++)
            arr[i] += arr[i - 1];

        long long int ans = LLONG_MAX;
        for (int i = sel; i <= num; i++) {
            long long int cnt = (arr[i] - arr[i - 1]) * sel - (arr[i] - arr[i - sel]);
            ans = min(ans, cnt);
        }
        
        cout << "Case #" << t << ": " << ans << endl;
    }

    return 0;
}