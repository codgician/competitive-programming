#include <bits/stdc++.h>
using namespace std;

#define SIZE 110

const int lim1 = 110;
const long long int lim2 = 110 * 110;
const auto p2int = [](int x, int y) { return x * lim1 + y; };
const auto p2ll = [](long long int x, long long int y) { if (x > y) swap(x, y); return 1ll * x * lim2 + y; };

int dirs[2][6] = {{-1, -1, 0, 1, 1, 0}, {-1, 0, 1, 1, 0, -1}};

string str[SIZE][SIZE]; int row, col, scr;
unordered_map<long long int, bool> mp; 

class State {
public:
    int turn, rem;
    int x, y, px, py;
    bool operator > (const State & snd) const {
        if (turn != snd.turn)
            return turn > snd.turn;
        return rem < snd.rem;       
    }
};

State dist[SIZE][SIZE]; bool vis[SIZE][SIZE];

void dijkstra(int sx, int sy) {
    for (int i = 0; i < row; i++)
        for (int j = 0; j < col; j++)
            vis[i][j] = false, dist[i][j] = {INT_MAX, -1, i, j, -1, -1};
    dist[sx][sy] = State{1, scr, sx, sy, -1, -1};
    priority_queue<State, vector<State>, greater<State> > pq;
    pq.push(dist[sx][sy]);

    while (!pq.empty()) {
        auto s = pq.top(); pq.pop();
        int x = s.x, y = s.y;
        if (vis[x][y])
            continue;
        vis[x][y] = true;
        for (int i = 0; i < 6; i++) {
            int x1 = x + dirs[0][i], y1 = y + dirs[1][i];
            const auto canMove = [x1, y1]() { return x1 >= 0 && y1 >= 0 && x1 < row && y1 < col; };
            if (!canMove() || str[x1][y1][0] == 'm')     // Cannot move to mountains
                continue;
            
            int cost = 1;   // Default cost
            if (str[x][y][0] == 'p' && str[x1][y1][0] == 'h')   // Move from plain to hill (terrian: 0)
                cost++;
            if (str[x1][y1][1] == 'f' || str[x1][y1][1] == 'm') // Move to forest or marsh (feature: 1)
                cost++;
            if (mp.find(p2ll(p2int(x, y), p2int(x1, y1))) != mp.end())  // River takes everything
                cost = s.rem;
            State s1 = s; s1.rem -= cost;
            if (s1.rem <= 0)
                s1.turn++, s1.rem = scr;
            s1.px = s.x, s1.py = s.y; s1.x = x1, s1.y = y1;
            if (dist[x1][y1] > s1)
                dist[x1][y1] = s1, pq.push(s1);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    cin >> col >> row;
    for (int i = 0; i < row; i++) 
        for (int j = 0; j < col; j++)
            cin >> str[i][j];

    int riverNum; cin >> riverNum;
    for (int i = 0; i < riverNum; i++) {
        int x1, y1, x2, y2; cin >> y1 >> x1 >> y2 >> x2;
        mp[p2ll(p2int(x1, y1), p2int(x2, y2))] = true;
    }

    int sx, sy, tx, ty; cin >> scr >> sy >> sx >> ty >> tx;
    dijkstra(sx, sy);

    if (dist[tx][ty].turn == INT_MAX) {
        cout << "They shall not pass\n";
        return 0;
    }

    cout << "Come this way\n";
    if (dist[tx][ty].turn > 1 && dist[tx][ty].rem == scr)
        dist[tx][ty].turn--;
    cout << dist[tx][ty].turn << '\n';
    vector<pair<int, int> > path;

    int x = tx, y = ty; path.push_back(make_pair(x, y));
    while (dist[x][y].px != -1) {
        tie(x, y) = make_tuple(dist[x][y].px, dist[x][y].py);
        path.push_back(make_pair(x, y));
    }
    reverse(path.begin(), path.end());
    cout << path.size() << '\n';
    for (const auto & p : path) {
        assert(str[p.first][p.second][0] != 'm');
        cout << p.second << ' ' << p.first << '\n';
    }
    return 0;
}