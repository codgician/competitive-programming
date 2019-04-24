#include <bits/stdc++.h>
using namespace std;

#define SIZE 10
#define BAG_SIZE 50

typedef struct _Node {
    int num, score;
} Node;

Node arr[SIZE];
int dp[SIZE][BAG_SIZE];

void insert(int * dp, int lim) {
    for (int i = lim; i < BAG_SIZE; i++)
        dp[i] = dp[i] + dp[i - lim];
}

void remove(int * dp, int lim) {
    for (int i = BAG_SIZE - 1; i >= lim; i--)
        dp[i] = dp[i] - dp[i - lim];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int caseNum;
    cin >> caseNum;
    while (caseNum--) {
        int siz, len;
        cin >> siz >> len;
        for (int i = 1; i <= len; i++)
            cin >> arr[i].score >> arr[i].num;
        dp[0][0] = 1;
        for (int i = 1; i <= len; i++) {
            for (int j = 0; j < BAG_SIZE; j++)
                dp[i][j] = dp[i - 1][j];
            remove(dp[i], (arr[i].num + 1) * arr[i].score);
            insert(dp[i], arr[i].score);
        }
        cout << dp[len][siz] << endl;
    }

    return 0;
}