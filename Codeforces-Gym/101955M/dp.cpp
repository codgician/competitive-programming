#include <bits/stdc++.h>
using namespace std;

#define SIZE 10010
#define BAG_SIZE 1010

const int mod = 1e9 + 7;

typedef struct _Node {
    int num, price;
} Node;

Node arr[SIZE];

long long int dpAdd[SIZE][BAG_SIZE], dpDel[SIZE][BAG_SIZE];

void insert(long long int * dp, int lim) {
    for (int i = lim; i < BAG_SIZE; i++) {
        dp[i] = (dp[i] + dp[i - lim]) % mod;
    }
}

void remove(long long int * dp, int lim) {
    for (int i = BAG_SIZE - 1; i >= lim; i--)
        dp[i] = (dp[i] - dp[i - lim] + mod) % mod;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    for (int i = 0; i < BAG_SIZE; i++)
        dpDel[0][i] = 1;
    dpAdd[0][0] = 1;
    int caseNum;
    cin >> caseNum;
    for (int t = 1; t <= caseNum; t++) {
        cout << "Case #" << t << ":\n";
        int len, qNum;
        cin >> len >> qNum;
        for (int i = 1; i <= len; i++)
            cin >> arr[i].num >> arr[i].price;
        for (int i = 1; i <= len; i++) {
            for (int j = 0; j < BAG_SIZE; j++)
                dpAdd[i][j] = dpAdd[i - 1][j], dpDel[i][j] = dpDel[i - 1][j];
            remove(dpAdd[i], (arr[i].num + 1) * arr[i].price);
            insert(dpAdd[i], arr[i].price);
            remove(dpDel[i], arr[i].price);
            insert(dpDel[i], (arr[i].num + 1) * arr[i].price);
        }

        int lastAns = 0;
        while (qNum--) {
            int qLeftPt, qRightPt, siz;
            cin >> qLeftPt >> qRightPt >> siz;
            qLeftPt = (qLeftPt + lastAns) % len + 1;
            qRightPt = (qRightPt + lastAns) % len + 1;
            if (qLeftPt > qRightPt)
                swap(qLeftPt, qRightPt);

            long long int ans = 0;
            for (int i = 0; i <= siz; i++) {
                ans = (ans + 1ll * dpAdd[qRightPt][i] * dpDel[qLeftPt - 1][siz - i] % mod) % mod;
            }
            cout << ans << "\n";
            lastAns = ans;
        }
    }

    return 0;
}