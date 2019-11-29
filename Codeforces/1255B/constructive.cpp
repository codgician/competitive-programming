#include <bits/stdc++.h>
using namespace std;
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
 
    int caseNum; cin >> caseNum;
    while (caseNum--) {
        int vertexNum, edgeNum; cin >> vertexNum >> edgeNum;
        long long int ans = 0; int fstMin = INT_MAX, sndMin = INT_MAX, fstPt = -1, sndPt = -1;
        for (int i = 0; i < vertexNum; i++) {
            int cnt; cin >> cnt; ans += cnt;
            if (cnt <= fstMin) {
                sndPt = fstPt; sndMin = fstMin;
                fstPt = i; fstMin = cnt;
            } else if (cnt <= sndMin) {
                sndPt = i; sndMin = cnt;
            }
        }
 
        if (vertexNum <= 2 || edgeNum < vertexNum) {
            cout << -1 << '\n';
            continue;
        }
        ans = ans * 2 + 1ll * (edgeNum - vertexNum) * (fstMin + sndMin);
        cout << ans << '\n';
        for (int i = 0; i < vertexNum; i++)
            cout << (i + 1) << ' ' << (i + 1) % vertexNum + 1 << '\n';
        for (int i = 0; i < edgeNum - vertexNum; i++)
            cout << fstPt + 1 << ' ' << sndPt + 1 << '\n';
    }
 
    return 0;
}