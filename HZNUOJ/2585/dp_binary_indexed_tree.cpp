#include <bits/stdc++.h>
using namespace std;

#define SIZE 2010

long long int price[SIZE], happi[SIZE];
long long int bitArr[SIZE], arr[SIZE], dp[SIZE][SIZE];

int lowbit(int n) {
    return n & -n;
}

void update(int pos, int val) {
    pos++;
    arr[pos] = val; // Original Array
    for (int i = pos; i < SIZE; i += lowbit(i)) {
        bitArr[i] = val;
        for (int j = 1; j < lowbit(i); j <<= 1) {
            bitArr[i] = max(bitArr[i], bitArr[i - j]);
        }
    }
}

long long int query(int leftPt, int rightPt) {
    leftPt++, rightPt++;
    long long int ans = LLONG_MIN;
    while (rightPt >= leftPt) {
        ans = max(ans, arr[rightPt]);
        rightPt--;
        while (rightPt - lowbit(rightPt) >= leftPt) {
            ans = max(ans, bitArr[rightPt]);
            rightPt -= lowbit(rightPt);
        }
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int num;
    cin >> num;
    for (int i = 1; i <= num; i++)
        cin >> price[i];
    for (int i = 1; i <= num; i++)
        cin >> happi[i];

    long long int ans = 0;
    memset(dp, -1, sizeof(dp));
    for (int j = 1; j <= num; j++) {
        dp[0][j] = happi[j];
        ans = max(ans, dp[0][j]);
    }

    for (int i = 1; i <= num; i++) {
        for (int j = 0; j < i; j++) 
            update(j, dp[j][i]);

        for (int j = i + 1; j <= num; j++) { 
            int cnt = 0;
            if (price[j] != 0)
                cnt = max(0ll, i - (j - i) * price[i] / price[j]);
            long long int cntMax = query(cnt, i - 1);
            if (cntMax == -1)
                continue;
            dp[i][j] = max(dp[i][j], cntMax + happi[j]);
            ans = max(ans, dp[i][j]);
        }
    }

    cout << ans << endl;
    return 0;
}