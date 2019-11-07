#include <bits/stdc++.h>
using namespace std;
 
#define SIZE 1000010
#define BUF_SIZE 7010
 
char str[BUF_SIZE][BUF_SIZE];
 
class Edge {
public:
    int to, next;
};
 
Edge edges[SIZE * 12];
int head[SIZE], edgesPt, vertexNum;
bool vis[SIZE];
 
void addEdge(int from, int to) {
    edges[edgesPt] = {to, head[from]};
    head[from] = edgesPt++;
}
 
int bfs(int startPt, int endPt) {
    for (int i = 0; i < vertexNum; i++)
        vis[i] = false;
    queue<pair<int, int> > q;
    q.push(make_pair(startPt, 1)); vis[startPt] = true;
    while (!q.empty()) {
        int cntPt = q.front().first, cntLen = q.front().second; q.pop();
        if (cntPt == endPt)
            return cntLen;
        for (int i = head[cntPt]; i != -1; i = edges[i].next) {
            int nextPt = edges[i].to;
            if (vis[nextPt])
                continue;
            vis[nextPt] = true;
            q.push(make_pair(nextPt, cntLen + 1));
        }
    }
    return -1;
}
 
int main() {
    int caseNum; scanf("%d", &caseNum);
    while (caseNum--) {
        int row, col; scanf("%d%d", &row, &col); getchar();
        int rr = 4 * row + 3, cc = 6 * col + 3; vertexNum = row * col;
        fill(head + 0, head + vertexNum, -1); edgesPt = 0;
        for (int i = 0; i < rr; i++) {
            gets(str[i]); int siz = strlen(str[i]);
            for (int j = siz; j < cc; j++)
                str[i][j] = ' ';
        }
 
        int startPt = -1, endPt = -1;
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                int from = i * col + j, x1 = 4 * i + 2, y1 = 6 * j + 4;
                if (j & 1)
                    x1 += 2;
 
                if (str[x1][y1] == 'S')
                    startPt = from;
                else if (str[x1][y1] == 'T')
                    endPt = from;
 
                if (x1 >= 2 && str[x1 - 2][y1] == ' ')
                    addEdge(from, from - col);
                if (x1 + 2 < rr && str[x1 + 2][y1] == ' ')
                    addEdge(from, from + col);
 
                if (x1 >= 1 && y1 >= 3 && str[x1 - 1][y1 - 3] == ' ')
                    (j & 1) ? addEdge(from, from - 1) : addEdge(from, from - col - 1);
                if (x1 + 1 < rr && y1 >= 3 && str[x1 + 1][y1 - 3] == ' ')
                    (j & 1) ? addEdge(from, from + col - 1) : addEdge(from, from - 1);
                if (x1 >= 1 && y1 + 3 < cc && str[x1 - 1][y1 + 3] == ' ')
                    (j & 1) ? addEdge(from, from + 1) : addEdge(from, from - col + 1);
                if (x1 + 1 < rr && y1 + 3 < cc && str[x1 + 1][y1 + 3] == ' ')
                    (j & 1) ? addEdge(from, from + col + 1) : addEdge(from, from + 1);
            }
        }
 
        printf("%d\n", bfs(startPt, endPt));
    }
 
    return 0;
}