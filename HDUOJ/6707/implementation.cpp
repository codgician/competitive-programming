#include <bits/stdc++.h>
using namespace std;

#define SIZE 100010

pair<int, int> arr[SIZE];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int len, qNum;
    cin >> len >> qNum;
    for (int i = 0; i < len; i++) {
        int cnt; cin >> cnt;
        arr[cnt] = make_pair(i, cnt);
    }

    int cntPos = 0;
    while (qNum--) {
        int cnt; cin >> cnt;
        arr[cnt].first = cntPos--; 
    }

    sort(arr + 1, arr + len + 1);
    for (int i = 1; i <= len; i++)
        cout << arr[i].second << ' ';
    
    return 0;
}