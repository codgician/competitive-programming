#include <bits/stdc++.h>
using namespace std;

#define SIZE 500010

class Edge {
public:
    int to, next, len;
};

Edge edges[SIZE << 1];
int head[SIZE], edgesPt;
int vertexNum, lim; long long int dp[SIZE][2];

void addEdge(int from, int to, int len) {
    edges[edgesPt] = {to, head[from], len};
    head[from] = edgesPt++;
}

void dfs(int cntPt, int fatherPt) {
    dp[cntPt][0] = 0; dp[cntPt][1] = 0;

    vector<long long int> vec;
    for (int i = head[cntPt]; i != -1; i = edges[i].next) {
        int nextPt = edges[i].to;
        if (nextPt == fatherPt)
            continue;
        dfs(nextPt, cntPt);
        dp[cntPt][0] += dp[nextPt][0]; dp[cntPt][1] += dp[nextPt][0];
        vec.push_back(-dp[nextPt][0] + dp[nextPt][1] + edges[i].len);
    }

    sort(vec.begin(), vec.end(), greater<long long int>());
    int siz = vec.size();
    for (int i = 0; i < min(siz, lim - 1) && vec[i] > 0; i++)
        dp[cntPt][0] += vec[i], dp[cntPt][1] += vec[i];
    for (int i = lim - 1; i < min(siz, lim) && vec[i] > 0; i++)
        dp[cntPt][0] += vec[i];
}
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int caseNum; cin >> caseNum;
    while (caseNum--) {
        cin >> vertexNum >> lim;
        fill(head + 0, head + vertexNum, -1); edgesPt = 0;
        for (int i = 1; i < vertexNum; i++) {
            int from, to, len; cin >> from >> to >> len;
            from--; to--; addEdge(from, to, len); addEdge(to, from, len);
        }
        dfs(0, -1); cout << dp[0][0] << '\n';
    }

    return 0;
}