#include <bits/stdc++.h>
using namespace std;

#define SIZE 1010
#define Q_SIZE 100010

typedef struct _Edge
{
    int to, next;
} Edge;
Edge edge[Q_SIZE];
int head[Q_SIZE], edgePt;

void addEdge(int from, int to) {
    edge[edgePt] = {to, head[from]};
    head[from] = edgePt++;
}

typedef struct  _Query
{
    int id, type, i, j;  
} Query;

Query qArr[Q_SIZE];
int ans[Q_SIZE];
int arr[SIZE][SIZE], cnt[SIZE], tag[SIZE];
int row, column, tot;

void dfs(int cntPt) {
    int totBak = tot;
    if (cntPt == 0) {
        for (int i = head[cntPt]; i != -1; i = edge[i].next) {
            int nextPt = edge[i].to;
            dfs(nextPt);
        }
        return;
    }

    int x = qArr[cntPt].i;
    if (qArr[cntPt].type == 3) {
        int cntNum = cnt[x];
        if (tag[x] == 1) {
            cntNum = column - cntNum;
        }
        tag[x] ^= 1;
        tot = tot - cntNum + (column - cntNum);
        ans[qArr[cntPt].id] = tot;
        for (int i = head[cntPt]; i != -1; i = edge[i].next) {
            int nextPt = edge[i].to;
            dfs(nextPt);
        }
        tag[x] ^= 1;
    } else if (qArr[cntPt].type == 4) {
        ans[qArr[cntPt].id] = tot;
        for (int i = head[cntPt]; i != -1; i = edge[i].next) {
            int nextPt = edge[i].to;
            dfs(nextPt);
        }
    } else {
        int y = qArr[cntPt].j;
        int arrBak = arr[x][y], cntBak = cnt[x];
        if ((tag[x] ^ arr[x][y]) == qArr[cntPt].type - 1) {
            arr[x][y] ^= 1;
            cnt[x] += (arr[x][y] << 1) - 1;
            tot += 3 - (qArr[cntPt].type << 1);
        }
        ans[qArr[cntPt].id] = tot;

        for (int i = head[cntPt]; i != -1; i = edge[i].next) {
            int nextPt = edge[i].to;
            dfs(nextPt);
        }

        arr[x][y] = arrBak;
        cnt[x] = cntBak;
    }

    tot = totBak;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    memset(arr, 0, sizeof(arr));
    memset(cnt, 0, sizeof(cnt));
    memset(tag, 0, sizeof(tag));
    memset(head, -1, sizeof(head));
    edgePt = 0, tot = 0;

    int qNum;
    cin >> row >> column >> qNum;

    for (int i = 1; i <= qNum; i++) {
        qArr[i].id = i;
        cin >> qArr[i].type >> qArr[i].i;
        if (qArr[i].type <= 3) {
            qArr[i].i--;
            if (qArr[i].type < 3) {
                 cin >> qArr[i].j;
                 qArr[i].j--;
            }
            addEdge(i - 1, i);
        } else {
            addEdge(qArr[i].i, i);
        }
    }

    dfs(0);

    for (int i = 1; i <= qNum; i++) {
        cout << ans[i] << endl;
    }

    return 0;
}