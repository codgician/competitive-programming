#include <bits/stdc++.h>
using namespace std;
 
const double eps = 1e-7;
 
class Vertex {
public:
    long long int x, y;
    bool operator == (const Vertex & snd) const {
        return x == snd.x && y == snd.y;
    }
    Vertex operator - (const Vertex & snd) const {
        return Vertex{x - snd.x, y - snd.y};
    }
    long long int operator * (const Vertex & snd) const {
        return x * snd.x + y * snd.y;
    }
};
 
class Seg {
public:
    Vertex leftPt, rightPt;
};
 
Vertex vtxs[3];
Seg segs[3];
 
int sgn(long long int x) {
    return x > 0 ? 1 : x < 0 ? -1 : 0;
}
 
long long int crossProd(const Vertex & fst, const Vertex & snd) {
    return fst.x * snd.y - snd.x * fst.y;
}
 
bool vtxOnSeg(const Vertex & vtx, const Seg & seg) {
    return sgn(crossProd(seg.rightPt - seg.leftPt, vtx - seg.leftPt)) == 0
        && sgn((vtx - seg.leftPt) * (vtx - seg.rightPt)) <= 0;
}
 
pair<double, double> solve(const Seg & seg, double rat) {
    return make_pair(rat * seg.leftPt.x + (1.0 - rat) * seg.rightPt.x, rat * seg.leftPt.y + (1.0 - rat) * seg.rightPt.y);
}
 
double dist(const Vertex & fst, const Vertex & snd) {
    return sqrt((fst.x - snd.x) * (fst.x - snd.x) + (fst.y - snd.y) * (fst.y - snd.y));
}
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
 
    int caseNum; cin >> caseNum;
    while (caseNum--) {
        for (int i = 0; i < 3; i++)
            cin >> vtxs[i].x >> vtxs[i].y;
        for (int i = 0; i < 3; i++) {
            segs[i].leftPt = vtxs[i];
            segs[i].rightPt = vtxs[(i + 1) % 3];
        }
 
        Vertex v; cin >> v.x >> v.y;
        pair<double, double> ret = make_pair(DBL_MAX, DBL_MAX);
        for (int i = 0; i < 3; i++) {
            if (v == vtxs[i]) {
                ret = solve(segs[(i + 1) % 3], 0.5);
                break;
            }
        }
 
        if (ret.first != DBL_MAX) {
            cout << fixed << setprecision(10) << ret.first << ' ' << ret.second << '\n';
            continue;
        }
 
        const auto which = [v]() {
            for (int i = 0; i < 3; i++)
                if (vtxOnSeg(v, segs[i]))
                    return i;
            return -1;
        };
 
        int sid = which();
        if (sid == -1) {
            cout << -1 << '\n';
            continue;
        }
 
        int diag = (sid - 1 + 3) % 3;
        double rat1 = dist(segs[sid].leftPt, v) / dist(segs[sid].leftPt, segs[sid].rightPt);
        if (abs(rat1 - 0.5) < eps) {
            cout << vtxs[diag].x << ' ' << vtxs[diag].y << '\n';
            continue;
        }
 
        if (rat1 < 0.5) {
            ret = solve(segs[(sid + 1) % 3], (0.5 - rat1) / (1.0 - rat1));
        } else {
            ret = solve(segs[(sid + 2) % 3], 0.5 / rat1);
        }
 
        cout << fixed << setprecision(10) << ret.first << ' ' << ret.second << '\n';
    }
 
    return 0;
}