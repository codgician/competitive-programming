#include <bits/stdc++.h>
using namespace std;

#define SIZE 200010

int parent[SIZE], arr[SIZE][26];

int getParent(int cntPt) {
    if (cntPt == parent[cntPt])
        return cntPt;
    parent[cntPt] = getParent(parent[cntPt]);
    return parent[cntPt];
}

bool merge(int fstPt, int sndPt) {
    fstPt = getParent(fstPt), sndPt = getParent(sndPt);
    if (fstPt == sndPt)
        return false;
    parent[sndPt] = fstPt;
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int len; cin >> len;
    for (int i = 0; i < len; i++) {
        string str; cin >> str;
        fill(arr[i] + 0, arr[i] + 26, 0);
        for (const auto & ch : str)
            arr[i][ch - 'a'] = 1;
        parent[i] = i;
    }

    for (int t = 0; t < 26; t++) {
        int prev = -1;
        for (int i = 0; i < len; i++) {
            if (arr[i][t] == 0)
                continue;
            if (prev == -1) {
                prev = i; continue;
            }
            merge(prev, i); prev = i;
        }
    }

    set<int> st;
    for (int i = 0; i < len; i++)
        st.insert(getParent(i));
    cout << st.size() << '\n';

    return 0;
}