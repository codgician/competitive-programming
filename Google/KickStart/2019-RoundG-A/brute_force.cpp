#include <bits/stdc++.h>
using namespace std;

#define SIZE 100010

int torns[SIZE], ques[SIZE];
pair<int, int> arr[SIZE];
long long int vis[SIZE];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int caseNum; cin >> caseNum;
    for (int t = 1; t <= caseNum; t++) {
        int pageNum, tornNum, qNum;
        cin >> pageNum >> tornNum >> qNum;
        fill(vis + 1, vis + pageNum + 1, 0);
        for (int i = 0; i < tornNum; i++)
            cin >> torns[i];
        for (int i = 0; i < qNum; i++)
            cin >> ques[i];
        sort(ques + 0, ques + qNum);

        int pt = 0; arr[pt] = make_pair(ques[0], 1);
        for (int i = 1; i < qNum; i++) {
            if (ques[i] == arr[pt].first)
                arr[pt].second++;
            else
                arr[++pt] = make_pair(ques[i], 1);
        }
        pt++;

        long long int ans = 0;
        for (int i = 0; i < pt; i++)
            for (int j = 1; 1ll * j * arr[i].first <= pageNum; j++)
                vis[j * arr[i].first] += arr[i].second, ans += arr[i].second;
        for (int i = 0; i < tornNum; i++)
            ans -= vis[torns[i]];
        cout << "Case #" << t << ": " << ans << '\n';
    }
 
    return 0;
}