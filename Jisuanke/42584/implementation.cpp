#include <bits/stdc++.h>
using namespace std;

int rad[2], dam[3], gunRld, brnLst;
int hp[2], def, siz, towerNum, pathLen, invNum, timeLen;

class Cord {
public:
    int x, y;
    bool operator == (const Cord & snd) const { return x == snd.x && y == snd.y; }
};

class Tower {
public:
    int type, rem;
    Cord loc;
};

pair<int, int> upd(const pair<int, int> & fst, const pair<int, int> & snd) {
    return fst.second + 1 < snd.first ? snd : make_pair(fst.first, snd.second);
}

class Invader {
public:
    int type, hp, ts, locPt;
    pair<int, int> brnRng;
    void shot() {  hp -= (type == 0 ? dam[0] : max(1, dam[0] - def)); }
    void fire(int t) {
        hp -= (type == 0 ? dam[1] : max(1, dam[1] - def)); 
        brnRng = upd(brnRng, make_pair(t + 1, t + brnLst)); 
    }
    void burn() { hp -= dam[2]; }
};

vector<Cord> path;
vector<Tower> towers;
vector<Invader> invaders;

int euclidDist2(const Cord & fst, const Cord & snd) {
    return (fst.x - snd.x) * (fst.x - snd.x) + (fst.y  - snd.y) * (fst.y - snd.y);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int caseNum; cin >> caseNum;
    for (int c = 1; c <= caseNum; c++) {
        path.clear(); towers.clear(); invaders.clear();
        cin >> siz >> towerNum >> pathLen >> invNum >> timeLen;
        for (int i = 0; i < pathLen; i++) {
            int x, y; cin >> x >> y;
            path.push_back(Cord{x, y});
        }
        cin >> rad[0] >> dam[0] >> gunRld >> rad[1] >> dam[1] >> brnLst >> dam[2];
        cin >> hp[0] >> hp[1] >> def;
        for (int i = 0; i < towerNum; i++) {
            int type, x, y; cin >> type >> x >> y;
            towers.push_back(Tower{type - 1, 0, Cord{x, y}});
        }
        string str; cin >> str;
        for (const auto & ch : str) {
            int type = ch - '1';
            invaders.push_back(Invader{type, hp[type], -1, -1, make_pair(-1, -1)});
        }

        for (int t = 1; t <= timeLen; t++) {
            // Enemy step
            for (int i = 0; i < min(t, invNum); i++) {
                auto & inv = invaders[i];
                if (inv.locPt < pathLen && inv.hp >= 0)   
                    inv.locPt++;
            }

            // Fire step
            for (auto & tow : towers) {
                if (tow.rem > 0) {
                    tow.rem--;
                    continue;
                }

                // Find target
                int pt = -1, dist = INT_MAX;
                for (int i = min(t, invNum) - 1; i >= 0; i--) {
                    const auto & inv = invaders[i];
                    if (inv.locPt >= pathLen)
                        continue;
                    if (inv.ts == -1) {
                        int dist1 = euclidDist2(tow.loc, path[inv.locPt]);
                        if (dist1 <= rad[tow.type] * rad[tow.type] && dist1 <= dist)
                            pt = i, dist = dist1;
                    }
                }
                
                if (pt == -1)
                    continue;
                if (tow.type == 0) {
                    invaders[pt].shot();
                    tow.rem = gunRld - 1;
                } else {
                    invaders[pt].fire(t);
                }
            }
            

            // Damage Estimation && End Step
            for (int i = 0; i < min(t, invNum); i++) {
                auto & inv = invaders[i];
                if (inv.locPt >= pathLen || inv.ts != -1)
                    continue;
                if (t >= inv.brnRng.first && t <= inv.brnRng.second)
                    inv.burn();
                if (inv.hp < 0) {
                    inv.ts = t;
                } else if (inv.locPt == pathLen - 1) {
                    inv.locPt++;
                }
            }
        }

        cout << "Case #" << c << ":\n";
        for (const auto & inv : invaders) {
            if (inv.hp < 0) {
                cout << "Be killed in the " << inv.ts << "-th frame at (" << path[inv.locPt].x << ',' << path[inv.locPt].y << ").\n";
            } else if (inv.locPt >= pathLen) {
                cout << "Arrive with " << inv.hp << " HP(s).\n";
            } else {
                cout << "Be alive at (" << path[inv.locPt].x << ',' << path[inv.locPt].y << ") with " << inv.hp << " HP(s).\n";
            }
        }
    }

    return 0;
}
