#include <bits/stdc++.h>
using namespace std;

#define SIZE 400010

vector<pair<int, int> > v;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int caseNum; cin >> caseNum;
    while (caseNum--) {
        int num, prev = -1; cin >> num; v.clear();
        for (int i = 0; i < num; i++) {
            int cnt; cin >> cnt;
            if (prev == -1 || prev != cnt) {
                v.push_back(make_pair(cnt, 1));
                prev = cnt;
            } else {
                v.back().second++;
            }
        }

        int g = v.front().second, s = 0, b = 0, cntNum = v.front().second, cntPt = 1;
        while (cntPt < (int)v.size() && cntNum + v[cntPt].second <= (num >> 1) && s <= g)
            s += v[cntPt].second, cntNum += v[cntPt].second, cntPt++;
        while (cntPt < (int)v.size() && cntNum + v[cntPt].second <= (num >> 1))
            b += v[cntPt].second, cntNum += v[cntPt].second, cntPt++;
        
        const auto validate = [g, s, b, num]() {
            return g + s + b <= (num << 1) && g < min(s, b) && min({g, s, b}) > 0;
        };

        if (validate()) {
            cout << g << ' ' << s << ' ' << b << '\n';
        } else {
            cout << "0 0 0 \n";
        }
    }

    return 0;
}