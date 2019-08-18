#include <bits/stdc++.h>
using namespace std;

#define SIZE 410
#define VERTEX_SIZE 168100
#define EDGE_SIZE 672400

class Edge {
public:
    int to, next;
    long double len;
};

Edge edges[EDGE_SIZE];
int head[VERTEX_SIZE], edgesPt;

void addEdge(int from, int to, long double len) {
    edges[edgesPt] = {to, head[from], len};
    head[from] = edgesPt++;
}

long double dist[VERTEX_SIZE]; bool isShortest[VERTEX_SIZE];

void dijkstra(int startPt, int vertexNum) {
    for (int i = 0; i < vertexNum; i++) {
        isShortest[i] = false;
        dist[i] = DBL_MAX;
    }
    priority_queue<pair<long double, int> > pq;
    pq.push(make_pair(0, startPt));
    dist[startPt] = 0;
    while (!pq.empty()) {
        int cntPt = pq.top().second;
        pq.pop();
        if (isShortest[cntPt])
            continue;
        isShortest[cntPt] = true;
        for (int i = head[cntPt]; i != -1; i = edges[i].next) {
            int nextPt = edges[i].to;
            if (dist[cntPt] != DBL_MAX && dist[nextPt] > dist[cntPt] + edges[i].len) {
                dist[nextPt] = dist[cntPt] + edges[i].len;
                pq.push(make_pair(-dist[nextPt], nextPt));
            }
        }
    }
}

vector<pair<int, int> > rows, cols;

class Rect {
public:
    int xl, yl, xr, yr;

    void read() {
        cin >> xl >> yl >> xr >> yr;
        rows.push_back(make_pair(xl, 0)); rows.push_back(make_pair(xr, 0));
        cols.push_back(make_pair(yl, 0)); cols.push_back(make_pair(yr, 0));
    }

    void discretize() {
        xl = lower_bound(rows.begin(), rows.end(), make_pair(xl, -1)) - rows.begin();
        xr = lower_bound(rows.begin(), rows.end(), make_pair(xr, -1)) - rows.begin();
        yl = lower_bound(cols.begin(), cols.end(), make_pair(yl, -1)) - cols.begin();
        yr = lower_bound(cols.begin(), cols.end(), make_pair(yr, -1)) - cols.begin();
    }
};

Rect arr[SIZE];

int dirs[2][4] = {1, -1, 0, 0, 0, 0, 1, -1};
int dep[SIZE][SIZE][4];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int caseNum; cin >> caseNum;
    while (caseNum--) {
        int num; cin >> num;
        rows.clear(); cols.clear();
        rows.push_back(make_pair(0, 0)); rows.push_back(make_pair(1e9, 0));
        cols.push_back(make_pair(0, 0)); cols.push_back(make_pair(1e9, 0));
        for (int i = 0; i < num; i++)
            arr[i].read();
        Rect pts; pts.read();

        sort(rows.begin(), rows.end()); rows.erase(unique(rows.begin(), rows.end()), rows.end());
        sort(cols.begin(), cols.end()); cols.erase(unique(cols.begin(), cols.end()), cols.end());

        int rowSiz = rows.size(), colSiz = cols.size();
        for (int i = 1; i < rowSiz; i++)
            rows[i].second = rows[i].first - rows[i - 1].first;
        for (int i = 1; i < colSiz; i++)
            cols[i].second = cols[i].first - cols[i - 1].first;

        memset(dep, 0, sizeof(dep));
        for (int i = 0; i < num; i++) {
            arr[i].discretize(); auto & rect = arr[i];
            for (int x = rect.xl; x <= rect.xr; x++) {
                for (int y = rect.yl; y <= rect.yr; y++) {
                    for (int i = 0; i < 4; i++) {
                        int x1 = x + dirs[0][i], y1 = y + dirs[1][i];
                        if (x1 < rect.xl || x1 > rect.xr || y1 < rect.yl || y1 > rect.yr)
                            continue;
                        dep[x][y][i]++;
                    }
                }
            }
        }

        const auto p2int = [colSiz](int x, int y) {
            return x * colSiz + y;
        };

        memset(head, -1, sizeof(head)); edgesPt = 0;
        for (int x = 0; x < rowSiz; x++) {
            for (int y = 0; y < colSiz; y++) {
                for (int i = 0; i < 4; i++) {
                    int x1 = x + dirs[0][i], y1 = y + dirs[1][i];
                    if (x1 < 0 || x1 >= rowSiz || y1 < 0 || y1 >= colSiz)
                        continue;
                    const auto getLen = [i, x, y, x1, y1]() {
                        if (x1 == x + 1) // x++
                            return rows[x1].second;
                        if (x1 == x - 1) // x--
                            return rows[x].second;
                        if (y1 == y + 1) // y++
                            return cols[y1].second;
                        return cols[y].second;
                    };
                    long double len = getLen();
                    addEdge(p2int(x, y), p2int(x1, y1), len / (dep[x][y][i] + 1));
                }
            }
        }

        pts.discretize();
        dijkstra(p2int(pts.xl, pts.yl), rowSiz * colSiz);
        cout << fixed << setprecision(5) << dist[p2int(pts.xr, pts.yr)] << '\n';
    }

    return 0;
}