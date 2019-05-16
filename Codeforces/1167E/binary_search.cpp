#include <bits/stdc++.h>
using namespace std;

#define SIZE 1000010

int leftPos[SIZE], rightPos[SIZE];
pair<int, int> leftMin[SIZE], rightMax[SIZE];
bool fst[SIZE], snd[SIZE];

/* Legal f(l, r) should satisfy:
  1. \max(R_1, ..., R_{l-1}) < \min(L_{r+1}, ..., L_x)
  2. \max(R_1, ..., R_{i-1}) < Li (\foreach i \in [2, l - 1])      => fst[i]
  3. \min(L_{i+1}, ..., L_x) > Ri (\foreach i \in [r + 1, x - 1])  => snd[i]
*/

bool check(int leftPt, int rightPt) {
    return rightMax[leftPt - 1].first <= leftMin[rightPt + 1].second && fst[leftPt - 1] && snd[rightPt + 1];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int len, maxVal;
    cin >> len >> maxVal;
    for (int i = 0; i <= maxVal + 1; i++) {
        leftPos[i] = INT_MAX, rightPos[i] = 0;
        leftMin[i] = make_pair(INT_MAX, INT_MAX);
        rightMax[i] = make_pair(0, 0);
    }

    for (int i = 1; i <= len; i++) {
        int cnt; cin >> cnt;
        leftPos[cnt] = min(leftPos[cnt], i);
        rightPos[cnt] = max(rightPos[cnt], i);
    }

    for (int i = 1; i <= maxVal; i++) {
        leftMin[i].first = min(leftMin[i - 1].first, leftPos[i]);
        rightMax[i].first = max(rightMax[i - 1].first, rightPos[i]);
    }
    for (int i = maxVal; i >= 1; i--) {
        leftMin[i].second = min(leftMin[i + 1].second, leftPos[i]);
        rightMax[i].second = max(rightMax[i + 1].second, rightPos[i]);
    }

    fst[0] = true, snd[maxVal + 1] = true;
    for (int i = 1; i <= maxVal && fst[i - 1]; i++)
        fst[i] = rightMax[i - 1].first <= leftPos[i];
    for (int i = maxVal; i >= 1 && snd[i + 1]; i--)
        snd[i] = leftMin[i + 1].second >= rightPos[i];

    long long int ans = 0;
    for (int i = 1; i <= maxVal; i++) {
        int bLeftPt = i, bRightPt = maxVal, bAns = -1;
        while (bLeftPt <= bRightPt) {
            int bMidPt = (bLeftPt + bRightPt) >> 1;
            if (check(i, bMidPt)) {
                bRightPt = bMidPt - 1;
                bAns = bMidPt;
            } else {
                bLeftPt = bMidPt + 1;
            }
        }
        if (bAns != -1)
            ans += maxVal - bAns + 1;
    }

    cout << ans << '\n';
    return 0;
}
