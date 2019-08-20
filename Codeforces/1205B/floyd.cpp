#include <bits/stdc++.h>
using namespace std;

#define SIZE 100010
#define FLO_SIZE 121

int dist[FLO_SIZE][FLO_SIZE], mat[FLO_SIZE][FLO_SIZE];
vector<long long int> vec;

int floyd(int vertexNum) {
    int ret = INT_MAX;
    for (int i = 0; i < vertexNum; i++)
        for (int j = 0; j < vertexNum; j++)
            dist[i][j] = mat[i][j];

    for (int k = 0; k < vertexNum; k++) {
        for (int i = 0; i < k; i++)
            for (int j = 0; j < i; j++)
                if (dist[i][j] != INT_MAX && mat[j][k] != INT_MAX && mat[k][i] != INT_MAX)
                    ret = min(ret, dist[i][j] + mat[j][k] + mat[k][i]);
        for (int i = 0; i < vertexNum; i++)
            for (int j = 0; j < vertexNum; j++)
                if (dist[i][k] != INT_MAX && dist[k][j] != INT_MAX)
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
    }

    return ret;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int len; cin >> len;
    for (int i = 0; i < len; i++) {
        long long int cnt; cin >> cnt;
        if (cnt != 0)
            vec.push_back(cnt);
    }

    len = vec.size();
    if (len > 120) {
        cout << 3 << '\n';
        return 0;
    }

    for (int i = 0; i < len; i++) {
        mat[i][i] = INT_MAX;
        for (int j = 0; j < i; j++) {
            mat[i][j] = (vec[i] & vec[j]) ? 1 : INT_MAX;
            mat[j][i] = mat[i][j];
        }
    }

    int ans = floyd(len);
    cout << (ans == INT_MAX ? -1 : ans) << '\n';
    return 0;
}
