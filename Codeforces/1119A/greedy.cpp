#include <bits/stdc++.h>
using namespace std;

#define SIZE 300010

int arr[SIZE];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int len;
    cin >> len; 
    for (int i = 0; i < len; i++) {
        cin >> arr[i];
    }

    int leftPt = 0;
    for (int i = 0; i < len; i++) {
        if (arr[i] != arr[len - 1]) {
            leftPt = i;
            break;
        }
    }

    int rightPt = 0;
    for (int i = len - 1; i >= 0; i--) {
        if (arr[i] != arr[0]) {
            rightPt = i;
            break;
        }
    }

    cout << max(len - 1 - leftPt, rightPt) << endl;
 
    return 0;
}