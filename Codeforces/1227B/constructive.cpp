#include <bits/stdc++.h>
using namespace std;
 
#define SIZE 100010
 
int pfx[SIZE], ans[SIZE];
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
 
    int caseNum; cin >> caseNum;
    while (caseNum--) {
        int len; cin >> len; set<int> st;
        for (int i = 1; i <= len; i++)
            st.insert(i);
        for (int i = 0; i < len; i++)
            cin >> pfx[i];
        ans[0] = pfx[0]; st.erase(pfx[0]);
        bool flag = true;
        for (int i = 1; i < len; i++) {
            if (pfx[i] != pfx[i - 1]) {
                if (st.find(pfx[i]) == st.end()) {
                    flag = false; break;
                }
                ans[i] = pfx[i]; st.erase(pfx[i]);
                continue;
            }
            if (st.empty() || *st.begin() > pfx[i]) {
                flag = false; break;
            }
            ans[i] = *st.begin(); st.erase(st.begin());
        }
 
        if (!flag) {
            cout << -1 << '\n';
        } else {
            for (int i = 0; i < len; i++)
                cout << ans[i] << ' ';
            cout << '\n';
        }
    }
 
    return 0;
}