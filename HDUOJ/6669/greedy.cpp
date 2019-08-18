#include <bits/stdc++.h>
using namespace std;

#define SIZE 1010

class Range {
public:
    int leftPt, rightPt;
};

Range arr[SIZE];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int caseNum; cin >> caseNum;
    while (caseNum--) {
        int len, arrPt = 0; Range cnt; cin >> len; 
        cin >> cnt.leftPt >> cnt.rightPt;
        for (int i = 1; i < len; i++) {
            int leftPt, rightPt; cin >> leftPt >> rightPt;
            if (rightPt < cnt.leftPt || leftPt > cnt.rightPt) {
                arr[arrPt++] = cnt;
                cnt = Range{leftPt, rightPt};
            } else {
                cnt.leftPt = max(cnt.leftPt, leftPt);
                cnt.rightPt = min(cnt.rightPt, rightPt);
            }
        }
        arr[arrPt++] = cnt;

        if (arrPt == 1) {
            cout << 0 << '\n';
            continue;
        }

        long long int ans = 0; int delta = 0, cntPt = arr[0].leftPt > arr[1].rightPt ? arr[0].leftPt : arr[0].rightPt;
        for (int i = 1; i < arrPt; i++) {
            int len = arr[i].rightPt - arr[i].leftPt + 1;
            if (arr[i].leftPt > cntPt) {
                cntPt += max(0, delta); delta = 0;
                int dist = arr[i].leftPt - cntPt;
                if (dist & 1) {
                    ans += (dist >> 1) + 1; cntPt = arr[i].leftPt;
                    if (len > 1)
                        cntPt++, delta = -1;
                } else {
                    ans += dist >> 1; cntPt = arr[i].leftPt;
                }
            } else {
                cntPt += min(0, delta); delta = 0;
                int dist = cntPt - arr[i].rightPt;
                if (dist & 1) {
                    ans += (dist >> 1) + 1; cntPt = arr[i].rightPt;
                    if (len > 1)
                        cntPt--, delta = 1;
                } else {
                    ans += dist >> 1; cntPt = arr[i].rightPt;
                }
            }
        }
        cout << ans << '\n';
    }

    return 0;
}