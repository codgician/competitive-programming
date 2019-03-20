#include <bits/stdc++.h>
using namespace std;

#define SIZE 27

vector<int> arr[2][SIZE];
vector<pair<int, int> > ans;

int id(char ch) {
    if (ch == '?')
        return 26;
    return ch - 'a';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int len;
    cin >> len;
    string fst, snd;
    cin >> fst >> snd;

    for (int i = 0; i < len; i++) {
        arr[0][id(fst[i])].push_back(i + 1);
        arr[1][id(snd[i])].push_back(i + 1);
    }

    for (int i = 0; i < 26; i++) {
        int pickNum = min(arr[0][i].size(), arr[1][i].size());
        while (pickNum--) {
            ans.push_back(make_pair(arr[0][i].back(), arr[1][i].back()));
            arr[0][i].pop_back();
            arr[1][i].pop_back();
        }
    }

    int leftNum = len - ans.size();
    int fstLeft = leftNum - arr[0][26].size(), sndLeft = leftNum - arr[1][26].size();

    int matchLeft = min(fstLeft, (int)arr[1][26].size());

    int pt = 0;
    while (matchLeft > 0 && pt < 26) {
        while (matchLeft > 0 && arr[0][pt].size() > 0) {
            ans.push_back(make_pair(arr[0][pt].back(), arr[1][26].back()));
            arr[0][pt].pop_back();
            arr[1][26].pop_back();
            matchLeft--;
        }
        pt++;
    }

    int matchRight = min(sndLeft, (int)arr[0][26].size());
    pt = 0;
    while (matchRight > 0 && pt < 26) {
        while (matchRight > 0 && arr[1][pt].size() > 0) {
            ans.push_back(make_pair(arr[0][26].back(), arr[1][pt].back()));
            arr[1][pt].pop_back();
            arr[0][26].pop_back();
            matchRight--;
        }
        pt++;
    }

    int matchQuest = min(arr[0][26].size(), arr[1][26].size());
    while (matchQuest--) {
        ans.push_back(make_pair(arr[0][26].back(), arr[1][26].back()));
        arr[0][26].pop_back();
        arr[1][26].pop_back();
    }

    cout << ans.size() << endl;
    for (auto i : ans) {
        cout << i.first << " " << i.second << endl;
    }

    return 0;
}