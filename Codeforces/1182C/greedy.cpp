#include <bits/stdc++.h>
using namespace std;

#define SIZE 100010

string arr[SIZE];
vector<int> vec[SIZE][30];
bool vis[SIZE];
vector<pair<int, int> > perfect, spare, inperfect, ans;

bool isVowel(char ch) {
    return ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    memset(vis, false, sizeof(vis));
    int num, maxNum = 0;
    cin >> num;
    for (int i = 0; i < num; i++) {
        int cntNum = 0, lastVowel = -1;
        cin >> arr[i];
        for (auto ch : arr[i]) {
           if (isVowel(ch)) {
                cntNum++;
                lastVowel = ch - 'a';
           }
        }
        assert(lastVowel != -1);
        vec[cntNum][lastVowel].push_back(i);
        maxNum = max(maxNum, cntNum);
    }

    for (int i = 0; i <= maxNum; i++) {
        for (int j = 0; j < 26; j++) {
            for (int k = 1; k < (int)vec[i][j].size(); k += 2) {
                perfect.push_back(make_pair(vec[i][j][k - 1], vec[i][j][k]));
            }
            if (vec[i][j].size() & 1) {
                if (spare.size() > 0 && spare.back().second == i) {
                    inperfect.push_back(make_pair(spare.back().first, vec[i][j].back()));
                    spare.pop_back();
                } else {
                    if (spare.size())
                        spare.pop_back();
                    spare.push_back(make_pair(vec[i][j].back(), i));
                }
            }
        }
    }

    unsigned int cntPt = 0;
    while (cntPt < min(inperfect.size(), perfect.size())) {
        ans.push_back(make_pair(inperfect[cntPt].first, perfect[cntPt].first));
        ans.push_back(make_pair(inperfect[cntPt].second, perfect[cntPt].second));
        cntPt++;
    }

    while (cntPt + 1 < perfect.size()) {
        ans.push_back(make_pair(perfect[cntPt].first, perfect[cntPt + 1].first));
        ans.push_back(make_pair(perfect[cntPt].second, perfect[cntPt + 1].second));
        cntPt += 2;
    }

    cout << ans.size() / 2 << '\n';
    for (auto p : ans)
        cout << arr[p.first] << " " << arr[p.second] << '\n';

    return 0;
}