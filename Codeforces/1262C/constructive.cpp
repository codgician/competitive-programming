#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int caseNum; cin >> caseNum;
    while (caseNum--) {
        int len, expt; string str, ret;
        cin >> len >> expt >> str;
        for (int i = 0; i < expt - 1; i++)
            ret.push_back('('), ret.push_back(')');
        int rem = len - ((expt - 1) << 1);
        for (int i = 0; i < (rem >> 1); i++)
            ret.push_back('(');
        for (int i = 0; i < (rem >> 1); i++)
            ret.push_back(')');
        
        vector<pair<int, int> > v;
        for (int i = 0; i < len; i++) {
            if (str[i] != ret[i]) {
                int revPt = i + 1;
                while (revPt < len && str[revPt] != ret[i])
                    revPt++;
                v.push_back(make_pair(i + 1, revPt + 1));
                reverse(str.begin() + i, str.begin() + revPt + 1);
            }
        }

        cout << v.size() << '\n';
        for (const auto & p : v)
            cout << p.first << ' ' << p.second << '\n';
    }

    return 0;
}