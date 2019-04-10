#include <bits/stdc++.h>
using namespace std;

#define SIZE 200010

int dp[SIZE], lft[SIZE], rgt[SIZE];
pair<int, int> arr[SIZE];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int len, num;
    cin >> len >> num;
    len++;
    for (int i = 1; i <= len; i++) 
        lft[i] = 0, rgt[i] = i - 1;

    for (int i = 0; i < num; i++) {
        int leftPt, rightPt;
        cin >> leftPt >> rightPt;
        arr[i] = make_pair(leftPt, rightPt);
        lft[rightPt + 1] = max(lft[rightPt + 1], leftPt);
        rgt[rightPt] = min(rgt[rightPt], leftPt - 1);
    }

    for (int i = 2; i <= len; i++)
        lft[i] = max(lft[i], lft[i - 1]);
    for (int i = len - 1; i >= 1; i--)
        rgt[i] = min(rgt[i], rgt[i + 1]);

    deque<int> mdq;
    mdq.push_back(0);
    dp[0] = 0;

    int pt = 1;
    for (int i = 1; i <= len; i++) {
        for (; pt <= rgt[i]; pt++) {
            if (dp[pt] == -1)
                continue;
            while (!mdq.empty() && dp[pt] > dp[mdq.back()])
                mdq.pop_back();
            mdq.push_back(pt);
        }
        while (!mdq.empty() && mdq.front() < lft[i])
            mdq.pop_front();
        if (!mdq.empty())
            dp[i] = max(dp[i], dp[mdq.front()] + 1);
        else
            dp[i] = -1;
    }

    cout << dp[len] - (dp[len] > 0) << endl; 
    return 0;
}