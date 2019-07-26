#include<bits/stdc++.h>
using namespace std;

#define SIZE 100010

vector<int> vec[SIZE], ans;
int med[SIZE];

int dp[SIZE][3][3], pre[SIZE][3][3];

int median(int fst, int snd, int thd) {
    int arr[3] = {fst, snd, thd};
    sort(arr + 0, arr + 3); return arr[1];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int caseNum; cin >> caseNum;
    while (caseNum--) {
        int len; cin >> len;
        for (int i = 0; i < len; i++) 
            vec[i].clear();
        for (int i = 1; i < len - 1; i++) {
            cin >> med[i];
            for (int j = i - 1; j <= i + 1; j++)
                vec[j].push_back(med[i]);
        }
        for (int i = 0; i < len; i++)
            sort(vec[i].begin(), vec[i].end());
        
        for (int i = 1; i <= len; i++)
            for (int j = 0; j < 3; j++)
                for (int k = 0; k < 3; k++)
                    dp[i][j][k] = false, pre[i][j][k] = -1;
        for (int j = 0; j < (int)vec[1].size(); j++)
            for (int k = 0; k < (int)vec[0].size(); k++)
                dp[1][j][k] = true;
                
        for (int i = 1; i < len - 1; i++) {
            for (int j = 0; j < (int)vec[i].size(); j++) {
                for (int k = 0; k < (int)vec[i - 1].size(); k++) {
                    if (!dp[i][j][k])
                        continue;
                    for (int l = 0; l < (int)vec[i + 1].size(); l++) 
                        if (median(vec[i - 1][k], vec[i][j], vec[i + 1][l]) == med[i])
                            dp[i + 1][l][j] = true, pre[i + 1][l][j] = k;
                }
            }
        }
        
        bool flag = false;
        for (int j = 0; j < (int)vec[len - 1].size() && !flag; j++) {
            for (int k = 0; k < (int)vec[len - 2].size(); k++) {
                if (dp[len - 1][j][k] == true) {
                    flag = true; ans.clear();
                    int i1 = len - 1, j1 = j, k1 = k;
                    while (i1 > 0) {
                        ans.push_back(vec[i1 - 1][k1]);
                        if (pre[i1][j1][k1] == -1)
                            break;
                        tie(i1, j1, k1) = make_tuple(i1 - 1, k1, pre[i1][j1][k1]);
                    }

                    for (int i = ans.size() - 1; i >= 0; i--)
                        cout << ans[i] << " ";
                    cout << vec[len - 1][j] << '\n';
                    break;
                }
            }
        }

        if (!flag)
            cout << -1 << '\n';
    }

    return 0;
}