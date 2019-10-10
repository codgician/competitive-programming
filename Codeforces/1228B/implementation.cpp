#include <bits/stdc++.h>
using namespace std;
 
#define SIZE 1010
const int mod = 1e9 + 7;
 
int arr[SIZE][SIZE];
 
long long int fastPow(long long int a, long long int n, long long int mod) {
    long long int ret = 1; a %= mod;
    while (n > 0) {
        if (n & 1)
            ret = (ret * a) % mod;
        a = (a * a) % mod; n >>= 1;
    }
    return ret;
}
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
 
    int row, col; cin >> row >> col;
    for (int i = 0; i < row; i++)
        for (int j = 0; j < col; j++)
            arr[i][j] = -1;
    
    for (int i = 0; i < row; i++) {
        int cnt; cin >> cnt;
        for (int j = 0; j < cnt; j++)
            arr[i][j] = 1;
        if (cnt < col)
            arr[i][cnt] = 0;
    }
 
    bool conflict = false;
    for (int j = 0; j < col && !conflict; j++) {
        int cnt; cin >> cnt;
        for (int i = 0; i < cnt && !conflict; i++)
            arr[i][j] == 0 ? conflict = true : arr[i][j] = 1;
        if (cnt < row)
            arr[cnt][j] == 1 ? conflict = true : arr[cnt][j] = 0;
    }
 
    if (conflict) {
        cout << 0 << '\n';
        return 0;
    }
 
    int num = 0;
    for (int i = 0; i < row; i++)
        for (int j = 0; j < col; j++)
            if (arr[i][j] == -1)
                num++;
    cout << fastPow(2, num, mod) << '\n';
 
    return 0;
}