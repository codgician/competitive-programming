#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
using namespace std;

#define SIZE 100010

int timeArr[SIZE], idArr[SIZE], recent[SIZE], tmp[5];
double scoreArr[SIZE];

tree<pair<double, int>, null_type, greater<pair<double, int> >, rb_tree_tag, tree_order_statistics_node_update> st;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    memset(recent, -1, sizeof(recent));
    int qNum, timePt = 0;
    cin >> qNum;
    while (qNum--) {
        char opr;
        cin >> opr;
        if (opr == 'Q') {
            // Query
            int rnk;
            cin >> rnk;
            auto it = st.find_by_order(rnk - 1);
            cout << idArr[-(it -> second)] << '\n';
        } else if (opr == 'R') {
            // Release
            int id, cntNum, maxTime = -1;
            double scr = 0;
            cin >> id >> cntNum;
            timeArr[id] = timePt; idArr[timePt++] = id;
            for (int i = 0; i < cntNum; i++) {
                cin >> tmp[i];
                if (recent[tmp[i]] != -1 && timeArr[recent[tmp[i]]] > maxTime) {
                    maxTime = timeArr[recent[tmp[i]]];
                    scr = scoreArr[recent[tmp[i]]];
                }
            }
            scoreArr[id] = scr;
            st.insert(make_pair(scr, -timeArr[id]));
            for (int i = 0; i < cntNum; i++)
                recent[tmp[i]] = id;
        } else {
            // Rate
            int id; double val;
            cin >> id >> val;
            auto it = st.lower_bound(make_pair(scoreArr[id], -timeArr[id]));
            st.erase(it);
            scoreArr[id] = (scoreArr[id] + val) / 2;
            st.insert(make_pair(scoreArr[id], -timeArr[id]));
        }
    }
    return 0;
}