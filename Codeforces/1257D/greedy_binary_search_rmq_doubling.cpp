#include <bits/stdc++.h>
using namespace std;

#define SIZE 200010

int mons[SIZE], lim[SIZE], st[SIZE][20];
pair<int, int> hero[SIZE];

void initSt(int len) {
    int logLim = log2(len) + 1;
    for (int i = 0; i < len; i++)
        st[i][0] = mons[i];
    for (int j = 1; j <= logLim; j++) {
        for (int i = 0; i < len; i++) {
            if (i + (1 << j) - 1 >= len)
                continue;
            st[i][j] = max(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
        }
    }
}

int queryMax(int qLeftPt, int qRightPt) {
    if (qLeftPt > qRightPt) return INT_MAX;
    int lenLog = log2(qRightPt - qLeftPt + 1);
    return max(st[qLeftPt][lenLog], st[qRightPt - (1 << lenLog) + 1][lenLog]);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int caseNum; cin >> caseNum;
    while (caseNum--) {
        int len; cin >> len;
        for (int i = 0; i < len; i++)
            cin >> mons[i];
        initSt(len);
        int num; cin >> num;
        for (int i = 0; i < num; i++)
            cin >> hero[i].first >> hero[i].second;
        sort(hero + 0, hero + num, [](const auto & fst, const auto & snd) { 
            return fst.second < snd.second; 
        });
        
        int cnt = 0, j = len;
        for (int i = num - 1; i >= 0; i--) {
            for (; j >= 0 && j > hero[i].second; j--)
                lim[j] = cnt;
            cnt = max(cnt, hero[i].first);
        }
        for (; j >= 0; j--)
            lim[j] = cnt;
        lim[0] = INT_MAX;

        int cntPt = 0, ans = 0;
        while (cntPt < len) {
            const auto getStep = [cntPt, len]() {
                int leftPt = 1, rightPt = len - cntPt, ret = 0;
                while (leftPt <= rightPt) {
                    int midPt = (leftPt + rightPt) >> 1; 
                    if (lim[midPt] >= queryMax(cntPt, cntPt + midPt - 1)) {
                        leftPt = midPt + 1; ret = midPt;
                    } else {
                        rightPt = midPt - 1;
                    }
                }
                return ret;
            };

            int step = getStep();
            if (step == 0) {
                ans = -1; break;
            }
            cntPt += step; ans++;
        }
        cout << ans << '\n';
    }

    return 0;
}