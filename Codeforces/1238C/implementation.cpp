#include <bits/stdc++.h>
using namespace std;

#define SIZE 200010

vector<int> vec;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    
    int caseNum; cin >> caseNum;
    while (caseNum--) {
        int height, len; cin >> height >> len; vec.clear();
        for (int i = 0; i < len; i++) {
            int cnt; cin >> cnt;
            vec.push_back(cnt);
        }
        vec.push_back(0); reverse(vec.begin(), vec.end());
        int cntHeight = height; vec.pop_back();

        int ret = 0;
        while (vec.size()) {
            int nextPt = vec.back();

            if (cntHeight == nextPt + 1) {
                int prevPt = nextPt; vec.pop_back();
                int op = 1;
                while (vec.size() && prevPt == nextPt + 1) {
                    nextPt = vec.back();
                    if (op) cntHeight = nextPt;
                    op ^= 1; prevPt = nextPt; vec.pop_back();
                }

                if (vec.empty())
                    break;
                nextPt = vec.back();

                if (cntHeight - nextPt <= 2) {
                    cntHeight = nextPt; vec.pop_back();
                } else {
                    ret++; cntHeight -= 2;
                }

                continue;
            }

            if (cntHeight == nextPt + 2) {
                cntHeight--;
                continue;
            }

            cntHeight = nextPt + 1;
        }

        cout << ret << '\n';
    }

    return 0;
}