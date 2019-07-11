#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

#define SIZE 101

int primeArr[SIZE], minFacArr[SIZE], primePt;
int dp[SIZE][SIZE];
vector<int> fac;

void initPrime() {
    fill(minFacArr + 0, minFacArr + SIZE, 0);
    primePt = 0;
    for (int i = 2; i < SIZE; i++) {
        if (minFacArr[i] == 0) {
            minFacArr[i] = i;
            primeArr[primePt++] = i;
        }
        for (int j = 0; j < primePt && primeArr[j] <= min(minFacArr[i], (SIZE - 1) / i); j++) {
            minFacArr[i * primeArr[j]] = primeArr[j];
        }
    }
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    initPrime();
    int caseNum; cin >> caseNum;
    while (caseNum--) {
        int len; cin >> len;
        for (int i = 0; i <= len; i++)
            for (int j = 0; j <= len; j++)
                dp[i][j] = 1;

        int ans = 1;
        for (int k = primeArr[0]; k <= len; k *= primeArr[0])
            for (int j = k; j <= len; j++)
                dp[0][j] = k, ans = max(ans, k);
        for (int i = 1; i < primePt && primeArr[i] <= len; i++) {
            for (int j = 0; j <= len; j++) {
                dp[i][j] = dp[i - 1][j];
                for (int k = primeArr[i]; k <= j; k *= primeArr[i]) {
                    dp[i][j] = max(dp[i][j], dp[i - 1][j - k] * k);
                    ans = max(ans, dp[i][j]);
                }
            }
        }

        cout << ans;
        fac.clear(); int sum = 0;
        for (int i = 0; i < primePt && primeArr[i] <= ans; i++) {
            if (ans % primeArr[i] != 0)
                continue;
            ans /= primeArr[i];
            int cnt = primeArr[i];
            while (ans % primeArr[i] == 0)
                ans /= primeArr[i], cnt *= primeArr[i];
            fac.push_back(cnt); sum += cnt;
        }
        if (ans > 1) {
            fac.push_back(ans); sum += ans;
        }

        sort(fac.begin(), fac.end());

        int delta = len - sum;
        if (delta)
            for (int i = 0; i < delta; i++)
                cout << " " << i + 1;

        int startPt = delta;
        for (int i = 0; i < (int)fac.size(); i++) {
            int endPt = startPt + fac[i] - 1;
            for (int j = startPt + 1; j <= endPt; j++)
                cout << " " << j + 1;
            cout << " " << startPt + 1;
            startPt = endPt + 1;
        }
        cout << '\n';
    }

    return 0;
}