#include <bits/stdc++.h>
using namespace std;

#define SIZE 200020

long long int arr[SIZE], dsc[SIZE];
int len;

bool check(int cntLim) {
    long long int last = LLONG_MIN;
    for (int i = 0; i < len; i++) {
        if (arr[i] > cntLim) {
            if (last > arr[i])
                return false;
            last = arr[i];
        }
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int caseNum;
    cin >> caseNum;
    while (caseNum--) {
        long long int leftPt = LLONG_MAX, rightPt = LLONG_MIN;
        cin >> len;
        for (int i = 0; i < len; i++) {
            cin >> arr[i];
            dsc[i] = arr[i];
            leftPt = min(leftPt, arr[i]);
            rightPt = max(rightPt, arr[i]);
        }
        leftPt -= 1; int lb = leftPt;

        sort(dsc + 0, dsc + len);

        long long int ans = leftPt;
        while (leftPt <= rightPt) {
            long long int midPt = (leftPt + rightPt) >> 1;
            if (check(midPt)) {
                rightPt = midPt - 1;
                ans = midPt;
            } else {
                leftPt = midPt + 1;
            }
        }

        if (ans == lb) {
            cout << 0 << '\n';
        } else {
            int ret = lower_bound(dsc + 0, dsc + len, ans + 1) - dsc;
            long long int cntMax = 0;
            for (int i = 0; i < len && cntMax <= ans; i++) {
                cntMax = max(cntMax, arr[i]);
                if (arr[i] == ans)
                    ret--; 
            }

            cout << ret << '\n';
        }
    }
    return 0;
}
