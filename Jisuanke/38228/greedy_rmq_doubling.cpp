#include <bits/stdc++.h>
using namespace std;

#define SIZE 500010

int arr[SIZE], len;
int lft[SIZE], rgt[SIZE];
pair<int, int> order[SIZE];
set<int> st;
vector<int> tmp;

long long int pfx[SIZE];
pair<long long int, long long int> stArr[SIZE][20];

pair<long long int, long long int> minMax(const pair<long long int, long long int> & fst, const pair<long long int, long long int> & snd) {
    return make_pair(min(fst.first, snd.first), max(fst.second, snd.second));
}

void initSt() {
    int logLim = log2(len + 1) + 1;
    for (int i = 0; i <= len; i++)
        stArr[i][0] = make_pair(pfx[i], pfx[i]);

    for (int j = 1; j <= logLim; j++) {
        for (int i = 0; i <= len; i++) {
            if (i + (1 << j) - 1 >= len + 1)
                continue;
            stArr[i][j] = minMax(stArr[i][j - 1], stArr[i + (1 << (j - 1))][j - 1]);
        }
    }
}

pair<long long int, long long int> queryMinMax(int qLeftPt, int qRightPt) {
    int lenLog = log2(qRightPt - qLeftPt + 1);
    return minMax(stArr[qLeftPt][lenLog], stArr[qRightPt - (1 << lenLog) + 1][lenLog]);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> len;
    pfx[0] = 0;
    for (int i = 1; i <= len; i++) {
        cin >> arr[i];
        pfx[i] = pfx[i - 1] + arr[i];
        order[i] = make_pair(arr[i], i);
    }

    initSt();
    sort(order + 1, order + len + 1);

    for (int i = 1; i <= len; i++) {
        if (st.empty()) {
            lft[order[i].second] = 1;
            rgt[order[i].second] = len;
        } else {
            auto it = st.lower_bound(order[i].second);
            if (it == st.begin()) {
                lft[order[i].second] = 1;
                rgt[order[i].second] = *it - 1;
            } else if (it == st.end()) {
                lft[order[i].second] = *prev(it) + 1;
                rgt[order[i].second] = len;
            } else {
                lft[order[i].second] = *prev(it) + 1;
                rgt[order[i].second] = *it - 1;
            }
        }

        tmp.push_back(order[i].second);
        if (i == len || order[i + 1].first > order[i].first) {
            for (auto j : tmp)
                st.insert(j);
            tmp.clear();
        }
    }

    long long int ans = INT_MIN;
    for (int i = 1; i <= len; i++) {
        pair<long long int, long long int> leftRet = queryMinMax(lft[i] - 1, i - 1);
        pair<long long int, long long int> rightRet = queryMinMax(i, rgt[i]);

        long long int minAns = (rightRet.first - leftRet.second) * arr[i];
        long long int maxAns = (rightRet.second - leftRet.first) * arr[i];
        ans = max(ans, max(minAns, maxAns));
    }
    cout << ans << endl;

    return 0;
}