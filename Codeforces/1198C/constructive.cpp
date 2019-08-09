#include <bits/stdc++.h>
using namespace std;

#define SIZE 300030

bool vis[SIZE];
vector<int> vec;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int caseNum; cin >> caseNum;
    while (caseNum--) {
        int vertexNum, edgeNum, matSiz = 0; vec.clear();
        cin >> vertexNum >> edgeNum;
        int lim = vertexNum; vertexNum *= 3;
        fill(vis + 0, vis + vertexNum, false);
        for (int i = 0; i < edgeNum; i++) {
            int from, to; cin >> from >> to; from--; to--;
            if (vis[from] || vis[to])
                continue;
            vis[from] = true; vis[to] = true; matSiz++;
            if (matSiz <= lim)
                vec.push_back(i);
        }
        
        if (matSiz >= lim) {
            cout << "Matching\n";
            for (const auto & i : vec)
                cout << i + 1 << ' ';
            cout << '\n';
        } else {
            cout << "IndSet\n";
            for (int i = 0; i < vertexNum && lim > 0; i++)
                if (!vis[i])
                    lim--, cout << i + 1 << ' ';
            cout << '\n';
        }
    }

    return 0;
}