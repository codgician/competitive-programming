#include <bits/stdc++.h>
using namespace std;

vector<int> vec;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int caseNum; cin >> caseNum;
    while (caseNum--) {
        int zero = -1; vec.clear();
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                int cnt; cin >> cnt;
                if (cnt == 0)
                    zero = i;
                else
                    vec.push_back(cnt);
            }
        }

        int invNum = 3 - zero;
        for (int i = 0; i < 15; i++)
            for (int j = i + 1; j < 15; j++)
                if (vec[i] > vec[j])
                    invNum++;
        cout << ((invNum & 1) ? "No\n" : "Yes\n");
    }

    return 0;
}