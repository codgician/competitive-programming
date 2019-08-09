#include <bits/stdc++.h>
using namespace std;
 
#define SIZE 100010
 
int arr[SIZE];
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
 
    int len, fst, snd; cin >> len >> fst >> snd;
    for (int i = 0; i < len; i++)
        cin >> arr[i];
    for (int i = 0; i < len; i++) {
        int minv = INT_MAX;
        for (int j = max(0, i - fst); j <= min(len - 1, i + snd); j++)
            minv = min(minv, arr[j]);
        if (minv == arr[i]) {
            cout << i + 1 << '\n';
            return 0;
        }
    }
 
    return 0;
}