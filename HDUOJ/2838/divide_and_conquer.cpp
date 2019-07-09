#include <bits/stdc++.h>
using namespace std;

#define SIZE 100010

long long int arr[SIZE], ans;

void divideConquer(int headPt, int tailPt) {
    if (headPt == tailPt)
        return;
    
    int midPt = (headPt + tailPt) >> 1;
    divideConquer(headPt, midPt);
    divideConquer(midPt + 1, tailPt);

    int j = midPt; long long int cntNum = 0, cntSum = 0;
    for (int i = tailPt; i > midPt; i--) {
        for (; j >= headPt && arr[j] >= arr[i]; j--)
            cntNum++, cntSum += arr[j];
        ans += cntNum * arr[i] + cntSum;
    }
        
    inplace_merge(arr + headPt, arr + midPt + 1, arr + tailPt + 1);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int len;
    while (cin >> len) {
        for (int i = 0; i < len; i++)
            cin >> arr[i];
        ans = 0;
        divideConquer(0, len - 1);
        cout << ans << '\n';
    }

    return 0;
}