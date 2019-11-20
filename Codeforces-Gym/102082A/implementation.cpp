#include <bits/stdc++.h>
using namespace std;
 
#define SIZE 1010
 
vector<string> arr[SIZE];
 
bool cmp(const vector<string> & fst, const vector<string> & snd) {
    const auto isNum = [](const string & s) { return s[0] >= '0' && s[0] <= '9'; };
    int siz = min(fst.size(), snd.size());
    for (int i = 0; i < siz; i++) {
        if (isNum(fst[i]) && isNum(snd[i])) {
            if (fst[i].size() != snd[i].size())
                return fst[i].size() < snd[i].size();
            if (fst[i] != snd[i])
                return fst[i] < snd[i];
        } else if (!isNum(fst[i]) && !isNum(snd[i])) {
            if (fst[i] != snd[i])
                return fst[i] < snd[i];
        } else {
            return isNum(fst[i]);
        }
    }
    return fst.size() <= snd.size();
}
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
 
    int len; cin >> len;
    for (int t = 0; t <= len; t++) {
        string str; cin >> str; int siz = str.size();
        string cnt;
        for (int i = 0; i < siz; i++) {
            if (str[i] >= '0' && str[i] <= '9') {
                cnt.push_back(str[i]);
                continue;
            }
            if (cnt.size()) {
                arr[t].push_back(cnt);
                cnt.clear();
            }
            cnt.push_back(str[i]);
            arr[t].push_back(cnt);
            cnt.clear();
        }
        if (cnt.size())
            arr[t].push_back(cnt);
    }
 
    for (int i = 1; i <= len; i++)
        cout << (cmp(arr[0], arr[i]) ? '+' : '-') << '\n';
    return 0;
}