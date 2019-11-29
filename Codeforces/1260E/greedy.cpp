#include <bits/stdc++.h>
using namespace std;
 
#define SIZE (1 << 18)
 
int arr[SIZE], len;
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
 
    int len, pos = len; cin >> len;
    priority_queue<int, vector<int>, greater<int> > pq;
    for (int i = 0; i < len; i++) {
        cin >> arr[i];
        if (arr[i] == -1)
            pos = i;
    }

    long long int ret = 0; int cntPos = len - 2;
    pq.push(arr[len - 1]);
    for (int l = len >> 1; l >= 1 && cntPos >= pos; l >>= 1) {
        auto tp = pq.top(); ret += tp; pq.pop();
        for (int i = 0; i < l && cntPos - i > pos; i++)
            pq.push(arr[cntPos - i]);
        cntPos -= l; 
    }
 
    cout << ret << '\n';
    return 0;
}
