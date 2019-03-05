#include <bits/stdc++.h>
using namespace std;

#define SIZE 100010
#define GRP_SIZE 310

const long long int mod = 1e9 + 7;

typedef struct _Edge {
    int to, next;
} Edge;

Edge arr[SIZE << 1];
int head[SIZE], arrPt, vertexNum;

int depth[SIZE], anc[SIZE][20], maxDepth;
int inClk[SIZE], outClk[SIZE], clkPt;
int cntArr[SIZE], bitArr[SIZE], ancNum[SIZE];
bool vis[SIZE];
long long int dp[GRP_SIZE];

int lowbit(int x) {
    return x & -x;
}

void add(int pos, int val) {
    for (int i = pos; i <= clkPt; i += lowbit(i)) {
        bitArr[i] += val;
    }
}

int prefixSum(int pos) {
    int ans = 0;
    for (int i = pos; i > 0; i -= lowbit(i)) {
        ans += bitArr[i];
    }
    return ans;
}

void addEdge(int from, int to) {
    arr[arrPt] = {to, head[from]};
    head[from] = arrPt++;
}

void dfs(int cntPt) {
    inClk[cntPt] = ++clkPt;
    for (int i = head[cntPt]; i != -1; i = arr[i].next) {
        int nextPt = arr[i].to;
        if (depth[nextPt] != -1)
            continue;
        depth[nextPt] = depth[cntPt] + 1;
        anc[nextPt][0] = cntPt;
        dfs(nextPt);
    }
    outClk[cntPt] = clkPt;
}

void st() {
    for (int j = 1; j <= maxDepth; j++)
        for (int i = 0; i < vertexNum; i++)
            if (anc[i][j - 1] != -1)
                anc[i][j] = anc[anc[i][j - 1]][j - 1];
}

int getLca(int fstPt, int sndPt) {
    if (depth[fstPt] > depth[sndPt])
        swap(fstPt, sndPt);
    for (int i = maxDepth; i >= 0; i--)
        if (anc[sndPt][i] != -1 && depth[anc[sndPt][i]] >= depth[fstPt])
            sndPt = anc[sndPt][i];
    if (fstPt == sndPt)
        return fstPt;
    for (int i = maxDepth; i >= 0; i--)
        if (anc[fstPt][i] != -1 && anc[sndPt][i] != -1 && anc[fstPt][i] != anc[sndPt][i])
            fstPt = anc[fstPt][i], sndPt = anc[sndPt][i];
    return anc[fstPt][0];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    memset(head, -1, sizeof(head));
    memset(depth, -1, sizeof(depth));
    memset(anc, -1, sizeof(anc));
    memset(bitArr, 0, sizeof(bitArr));
    memset(vis, false, sizeof(vis));
    arrPt = 0, clkPt = 0;

    int qNum;
    cin >> vertexNum >> qNum;
    maxDepth = log2(vertexNum) + 1;
    for (int i = 1; i < vertexNum; i++) {
        int from, to;
        cin >> from >> to;
        from--, to--;
        addEdge(from, to);
        addEdge(to, from);
    }

    depth[0] = 0;
    dfs(0);
    st();

    while (qNum--) {
        int num, grpNum, rootPt;
        cin >> num >> grpNum >> rootPt;
        rootPt--;
        for (int i = 0; i < num; i++) {
            cin >> cntArr[i];
            cntArr[i]--;
            vis[cntArr[i]] = true;
            add(inClk[cntArr[i]], 1);
            add(outClk[cntArr[i]] + 1, -1);
        }

        int rootAnc = prefixSum(inClk[rootPt]); 
        for (int i = 0; i < num; i++) {
            int lcaPt = getLca(rootPt, cntArr[i]);
            ancNum[i] = rootAnc + prefixSum(inClk[cntArr[i]]) - (prefixSum(inClk[lcaPt]) * 2) - (vis[lcaPt] == false);
        }

        for (int i = 0; i < num; i++) {
            vis[cntArr[i]] = false;
            add(inClk[cntArr[i]], -1);
            add(outClk[cntArr[i]] + 1, 1);
        }

        sort(ancNum + 0, ancNum + num);

        if (ancNum[num - 1] >= grpNum) {
            cout << 0 << endl;
            continue;
        }

        memset(dp, 0, sizeof(dp));
        dp[0] = 1;
        for (int i = 0; i < num; i++) {
            for (int j = min(i + 1, grpNum); j >= 0; j--) {
                if (j <= ancNum[i])
                    dp[j] = 0;
                else
                    dp[j] = (dp[j] * (j - ancNum[i]) % mod + dp[j - 1]) % mod;
            }
        }

        long long int ans = 0;
        for (int j = 1; j <= grpNum; j++) {
            ans = (ans + dp[j]) % mod;
        }
        cout << ans << endl;
    }

    return 0;
}