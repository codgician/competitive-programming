#include <bits/stdc++.h>
using namespace std;
 
int arr[20];
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
 
    int caseNum; cin >> caseNum;
    while (caseNum--) {
        int minv = INT_MAX, mink = -1;
        for (int i = 0; i <= 9; i++) {
            cin >> arr[i]; arr[i] += i == 0;
            if (arr[i] < minv) {
                minv = arr[i];
                mink = i;
            }
        }
 
        if (mink == 0) {
            cout << 1;
            for (int i = 0; i < minv; i++)
                cout << 0;
            cout << '\n';
        } else {
            for (int i = 0; i <= minv; i++)
                cout << mink;
            cout << '\n';
        }
    }
 
    return 0;
}