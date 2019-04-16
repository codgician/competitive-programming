#include <bits/stdc++.h>
using namespace std;

#define SIZE 50
const long long int mod = 1e9 + 7;

bool arr[SIZE][SIZE];
long long int weight[SIZE], sqrSum, sum, num;
pair<int, int> deg[SIZE];
int vis[SIZE], vertexNum, edgeNum;

long long int quickPow(long long int a, long long int n) {
    long long int ans = 1;
    a %= mod;
    while (n > 0) {
        if (n & 1)
            ans = (ans * a) % mod;
        a = (a * a) % mod;
        n >>= 1;
    }
    return ans;
}

void dfs(int cntPt, long long int cntNum, long long int cntSum, long long int cntSqrSum) {
    int nextPt = cntPt + 1;
    while (nextPt < vertexNum && vis[deg[nextPt].second])
        nextPt++;

    if (nextPt == vertexNum) {
        num = (num + cntNum) % mod;
        sum = (sum + cntSum) % mod;
        sqrSum = (sqrSum + cntSqrSum) % mod;
        return;
    }

    int nextId = deg[nextPt].second;

    bool hasConf = false;
    for (int i = cntPt + 1; i < vertexNum && !hasConf; i++)
        if (arr[nextId][deg[i].second])
            hasConf = true;

    if (!hasConf) {
        long long int nextSum = cntSum * (1 + weight[nextId]) % mod;
        long long int nextSqrSum = cntSqrSum * (1 + weight[nextId] * weight[nextId] % mod) % mod;
        dfs(nextPt, (cntNum << 1) % mod, nextSum, nextSqrSum);
        return;
    }

    // Skip nextPt
    dfs(nextPt, cntNum, cntSum, cntSqrSum);

    // Select nextPt
    for (int i = cntPt + 1; i < vertexNum; i++)
        if (arr[nextId][deg[i].second])
            vis[deg[i].second]++;
    long long int nextSum = cntSum * weight[nextId] % mod;
    long long int nextSqrSum = cntSqrSum * weight[nextId] % mod * weight[nextId] % mod;
    dfs(nextPt, cntNum, nextSum, nextSqrSum);
    for (int i = cntPt + 1; i < vertexNum; i++)
        if (arr[nextId][deg[i].second])
            vis[deg[i].second]--;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> vertexNum >> edgeNum;
    memset(arr, false, sizeof(arr));
    for (int i = 0; i < vertexNum; i++) {
        deg[i] = make_pair(0, i);
        cin >> weight[i];
    }

    for (int i = 0; i < edgeNum; i++) {
        int from, to;
        cin >> from >> to;
        from--, to--;
        arr[from][to] = true;
        arr[to][from] = true;
        deg[from].first++, deg[to].first++;
    }

    sort(deg + 0, deg + vertexNum, greater<pair<int, int> >());

    sqrSum = 1, sum = 1, num = 1;
    memset(vis, 0, sizeof(vis));
    for (int i = 0; i < vertexNum; i++) {
        int cntId = deg[i].second;
        for (int j = i + 1; j < vertexNum; j++)
            if (arr[cntId][deg[j].second])
                vis[deg[j].second]++;
        dfs(i, 1, weight[cntId], weight[cntId] * weight[cntId] % mod);
        for (int j = i + 1; j < vertexNum; j++)
            if (arr[cntId][deg[j].second])
                vis[deg[j].second]--;
    }

    long long int numInv = quickPow(num, mod - 2);
    long long int ans = (sqrSum * numInv % mod - sum * sum % mod * numInv % mod * numInv % mod + mod) % mod;
    cout << ans << endl;

    return 0;
}