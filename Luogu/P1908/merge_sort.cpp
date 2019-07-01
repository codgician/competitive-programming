#include <bits/stdc++.h>
using namespace std;

#define SIZE 500010

int arr[SIZE];
long long int ans;

void divideConquer(int headPt, int tailPt) {
    if (headPt == tailPt)
        return;
    int midPt = (headPt + tailPt) >> 1;
    divideConquer(headPt, midPt);
    divideConquer(midPt + 1, tailPt);

    int j = headPt, cntNum = midPt - headPt + 1;
    for (int i = midPt + 1; i <= tailPt; i++) {
        for (; arr[j] <= arr[i] && j <= midPt; j++)
            cntNum--;
        ans += cntNum;
    }

    inplace_merge(arr + headPt, arr + midPt + 1, arr + tailPt + 1);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int len; cin >> len;
    for (int i = 0; i < len; i++)
        cin >> arr[i];
    ans = 0;
    divideConquer(0, len - 1);
    
    cout << ans << '\n';
    return 0;
}