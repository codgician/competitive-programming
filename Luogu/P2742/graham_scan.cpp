#include <bits/stdc++.h>
using namespace std;

#define SIZE 10010

typedef struct _Vertex {
    double x, y;
    bool operator < (const struct _Vertex & snd) const {
        if (x != snd.x)
            return x < snd.x;
        return y < snd.y;
    }
} Vertex;

Vertex arr[SIZE];

vector<int> vec;
int vertexNum;

double crossedProd(const Vertex & fst, const Vertex & snd) {
    return fst.x * snd.y - snd.x * fst.y;
}

double dist(const Vertex & fst, const Vertex & snd) {
    return sqrt(pow(fst.x - snd.x, 2) + pow(fst.y - snd.y, 2));
}

Vertex vtxMinus(const Vertex & fst, const Vertex & snd) {
    return {fst.x - snd.x, fst.y - snd.y};
}

bool isLeft(const Vertex & fst, const Vertex & snd, const Vertex & thd) {
    return crossedProd(vtxMinus(snd, fst), vtxMinus(thd, fst)) > 0;
}

void graham(int which) { 
    vec.clear(); vec.push_back(0); vec.push_back(1);
    for (int i = 2; i < vertexNum; i++) {
        while (vec.size() > 1 && (which ^ isLeft(arr[i], arr[vec[vec.size() - 1]], arr[vec[vec.size() - 2]])))
            vec.pop_back();
        vec.push_back(i);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    cin >> vertexNum;
    for (int i = 0; i < vertexNum; i++)
        cin >> arr[i].x >> arr[i].y;
    sort(arr + 0, arr + vertexNum);

    if (vertexNum <= 1) {
        cout << "0.00\n";
        return 0;
    }

    double ans = 0;

    for (int t = 0; t < 2; t++) {
        graham(t);
        for (unsigned int i = 0; i < vec.size() - 1; i++)
            ans += dist(arr[vec[i]], arr[vec[i + 1]]);
    }

    cout << fixed << setprecision(2) << ans << '\n';
    return 0;
}