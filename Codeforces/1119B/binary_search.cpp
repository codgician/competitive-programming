#include <bits/stdc++.h>
using namespace std;

#define SIZE 1010

long long int arr[SIZE], tmp[SIZE], height;

bool check(int cntNum) {
    for (int i = 0; i < cntNum; i++)
        tmp[i] = arr[i];
    sort(tmp + 0, tmp + cntNum, greater<int>());
    long long int cnt = 0;
    for (int i = 0; i < cntNum; i += 2)
        cnt += tmp[i];
    return cnt <= height;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int num;
    cin >> num >> height;
    for (int i = 0; i < num; i++)
        cin >> arr[i];

    int leftPt = 0, rightPt = num, ans = 0;
    while (leftPt <= rightPt) {
        int midPt = (leftPt + rightPt) >> 1;
        if (check(midPt)) {
            leftPt = midPt + 1;
            ans = midPt;
        } else {
            rightPt = midPt - 1;
        }
    }
    cout << ans << endl;
    return 0;
}