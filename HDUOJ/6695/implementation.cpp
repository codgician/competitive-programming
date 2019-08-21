#include <bits/stdc++.h>
using namespace std;

#define SIZE 200020

class Node {
public:
    long long int sing, talk;
    bool operator < (const Node & snd) const {
        return sing < snd.sing;
    }
};

Node arr[SIZE]; int len;
map<long long int, vector<int> > mp;

long long int sts[SIZE][20];

void initSt() {
    int logLim = log2(len) + 1;
    for (int i = 0; i < len; i++)
        sts[i][0] = arr[i].talk;
    for (int j = 1; j <= logLim; j++) {
        for (int i = 0; i < len; i++) {
            if (i + (1 << j) - 1 >= len)
                continue;
            sts[i][j] = max(sts[i][j - 1], sts[i + (1 << (j - 1))][j - 1]);
        }
    }
}

long long int queryMax(int qLeftPt, int qRightPt) {
    int lenLog = log2(qRightPt - qLeftPt + 1);
    return max(sts[qLeftPt][lenLog], sts[qRightPt - (1 << lenLog) + 1][lenLog]);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int caseNum; cin >> caseNum;
    while (caseNum--) {
        cin >> len; mp.clear();
        for (int i = 0; i < len; i++)
            cin >> arr[i].sing >> arr[i].talk;
        sort(arr + 0, arr + len);
        for (int i = 0; i < len; i++)
            mp[arr[i].talk].push_back(i);
        initSt();

        long long int ans = LLONG_MAX;
        for (int i = 0; i < len; i++) {
            auto it = mp.lower_bound(arr[i].sing);
            vector<pair<long long int, int> > vec;

            if (it != mp.end()) {
                auto & v = it -> second;
                if (v.back() != i) {
                    vec.push_back(make_pair(it -> first, v.back()));
                } else if (v.size() > 1) {
                    vec.push_back(make_pair(it -> first, v[v.size() - 2]));
                } else {
                    auto nit = next(it);
                    if (nit != mp.end())
                        vec.push_back(make_pair(nit -> first, nit -> second.back()));
                }
            }
            if (it != mp.begin()) {
                it = prev(it); auto & v = it -> second;
                if (v.back() != i) {
                    vec.push_back(make_pair(it -> first, v.back()));
                } else if (v.size() > 1) {
                    vec.push_back(make_pair(it -> first, v[v.size() - 2]));
                } else {
                    auto pit = prev(it);
                    if (pit != mp.end())
                        vec.push_back(make_pair(pit -> first, pit -> second.back()));
                }
            }

            for (const auto & p : vec) {
                long long int maxTalk = -1;
                if (i + 1 < len)
                    maxTalk = queryMax(i + 1, len - 1);
                if (maxTalk > p.first) {
                    ans = min(ans, llabs(maxTalk - arr[i].sing));
                } else {
                    ans = min(ans, llabs(p.first - arr[i].sing));
                }
            }
        }

        cout << ans << '\n';
    }

    return 0;
}