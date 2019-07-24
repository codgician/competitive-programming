#include <bits/stdc++.h>
using namespace std;

typedef struct _Vertex {
    long long int x, y;
    bool operator < (const struct _Vertex & snd) const {
        if (x != snd.x)
            return x < snd.x;
        return y < snd.y;
    }
} Vertex;

typedef struct _Seg {
    Vertex startPt, endPt;
} Seg;

vector<Vertex> vertices[2], convexHull[2]; int vertexNum;
vector<int> vec;

long long int crossedProd(const Vertex & fst, const Vertex & snd) {
    return fst.x * snd.y - snd.x * fst.y;
}

Vertex vtxMinus(const Vertex & fst, const Vertex & snd) {
    return {fst.x - snd.x, fst.y - snd.y};
}

bool isLeft(const Vertex & fst, const Vertex & snd, const Vertex & thd) {
    return crossedProd(vtxMinus(snd, fst), vtxMinus(thd, fst)) > 0;
}

void graham(vector<Vertex> & cnt, int which) { 
    vec.clear(); 
    if (cnt.size() < 1)
        return;
    vec.push_back(0); 
    if (cnt.size() < 2)
        return;
    vec.push_back(1);
    for (int i = 2; i < (int)cnt.size(); i++) {
        while (vec.size() > 1 && (which ^ isLeft(cnt[i], cnt[vec[vec.size() - 1]], cnt[vec[vec.size() - 2]])))
            vec.pop_back();
        vec.push_back(i);
    }
}

bool segIntersect(const Seg & fst, const Seg & snd) {
    long long int cp1 = crossedProd(vtxMinus(fst.endPt, fst.startPt), vtxMinus(snd.startPt, fst.startPt));
    long long int cp2 = crossedProd(vtxMinus(fst.endPt, fst.startPt), vtxMinus(snd.endPt, fst.startPt));
    long long int cp3 = crossedProd(vtxMinus(snd.endPt, snd.startPt), vtxMinus(fst.startPt, snd.startPt));
    long long int cp4 = crossedProd(vtxMinus(snd.endPt, snd.startPt), vtxMinus(fst.endPt, snd.startPt));
    return cp1 * cp2 <= 0 && cp3 * cp4 <= 0
        && max(snd.startPt.x, snd.endPt.x) >= min(fst.startPt.x, fst.endPt.x) 
        && max(fst.startPt.x, fst.endPt.x) >= min(snd.startPt.x, snd.endPt.x)
        && max(snd.startPt.y, snd.endPt.y) >= min(fst.startPt.y, fst.endPt.y) 
        && max(fst.startPt.y, fst.endPt.y) >= min(snd.startPt.y, snd.endPt.y);
}

bool convexHullIntersect(vector<Vertex> & fst, vector<Vertex> & snd) {
    int fstLen = fst.size(), sndLen = snd.size();
    for (int i = 0; i < fstLen; i++) {
        int i1 = (i + 1) % fstLen;
        for (int j = 0; j < sndLen; j++) {
            int j1 = (j + 1) % sndLen;
            if (segIntersect({fst[i], fst[i1]}, {snd[j], snd[j1]}))
                return true;
        }
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int caseNum; cin >> caseNum;
    while (caseNum--) {
        int num; cin >> num;
        vertices[0].clear(); convexHull[0].clear();
        vertices[1].clear(); convexHull[1].clear();

        while (num--) {
            int x1, x2, y; cin >> x1 >> x2 >> y;
            vertices[(y > 0 ? 0 : 1)].push_back({x1, x2});
        }

        for (int t = 0; t < 2; t++) {
            sort(vertices[t].begin(), vertices[t].end());
            graham(vertices[t], 0);
            for (auto i : vec)
                convexHull[t].push_back(vertices[t][i]);
            graham(vertices[t], 1);
            for (int i = vec.size() - 2; i > 0; i--)
                convexHull[t].push_back(vertices[t][vec[i]]);
        }

        cout << (convexHullIntersect(convexHull[0], convexHull[1]) ? "Infinite loop!\n" : "Successful!\n");
    }

    return 0;
}