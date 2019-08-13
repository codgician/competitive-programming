#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;

#define SIZE 100010

const unsigned int mul = 20190812;
const int lim = 1e9;

class Magic {
public:
    Magic(unsigned int state): state(state), ans(0) {}

    unsigned long long int retrieve() {
        unsigned int modulo = 0x7fffffff;
        state = (1ull * state * mul + ans) % modulo;
        unsigned int high = state;
        state = (1ull * state * mul + ans) % modulo;
        return high * modulo + state;
    }

    int retrieve(int a, int b) {
        assert (a <= b);
        return (int) (retrieve() % (b - a + 1)) + a;
    }

    void submit(unsigned int k) {
        ans = ans * mul + k;
    }
  
    unsigned int retrieveAns() {
        return ans;
    }

private:
    unsigned int state, ans;
};

class Vertex {
public:
    int id; long long int x, y;
    bool operator < (const Vertex & snd) const {
        if (x != snd.x)
            return x < snd.x;
        return y < snd.y;
    }
};

Vertex arr[SIZE]; bool vis[SIZE];
vector<Vertex> vec, cvxhull, vertices;

long long int crossedProd(const Vertex & fst, const Vertex & snd) {
    return fst.x * snd.y - snd.x * fst.y;
}

long long int dotProd(const Vertex & fst, const Vertex & snd) {
    return fst.x * snd.x + fst.y * snd.y;
}

Vertex vtxMinus(const Vertex & fst, const Vertex & snd) {
    return {-1, fst.x - snd.x, fst.y - snd.y};
}

bool isLeft(const Vertex & fst, const Vertex & snd, const Vertex & thd) {
    return crossedProd(vtxMinus(snd, fst), vtxMinus(thd, fst)) > 0;
}

void graham(vector<Vertex> & cnt, int which) {
    vec.clear(); 
    if (cnt.size() < 1)
        return;
    vec.push_back(cnt[0]); 
    if (cnt.size() < 2)
        return;
    vec.push_back(cnt[1]);
    for (int i = 2; i < (int)cnt.size(); i++) {
        while (vec.size() > 1 && (which ^ isLeft(cnt[i], vec[vec.size() - 1], vec[vec.size() - 2])))
            vec.pop_back();
        vec.push_back(cnt[i]);
    }
}

void convexHull() {
    cvxhull.clear();
    sort(vertices.begin(), vertices.end());
    graham(vertices, 0);
    for (auto i : vec)
        cvxhull.push_back(i);
    graham(vertices, 1);
    for (int i = vec.size() - 2; i > 0; i--)
        cvxhull.push_back(vec[i]);
}

__gnu_pbds::tree<
    int,
    __gnu_pbds::null_type,
    less<int>,
    __gnu_pbds::rb_tree_tag,
    __gnu_pbds::tree_order_statistics_node_update
> st;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int caseNum; cin >> caseNum;
    while (caseNum--) {
        vertices.clear(); st.clear(); cvxhull.clear();
        unsigned int state; string str; int idPt = 0; 
        bool rebuild = false, update = false;
        cin >> state >> str;
        Magic magic(state);

        for (const char & ch : str) {
            if (ch == 'a') {
                // Add vertex
                int x = magic.retrieve(-lim, lim);
                int y = magic.retrieve(-lim, lim);
                arr[++idPt] = Vertex{idPt, x, y};
                vertices.push_back(arr[idPt]);
                st.insert(idPt); vis[idPt] = true; update = true;
                //cerr << "add: #" << idPt << " x = " << x << " y = " << y << endl; 
            } else if (ch == 'e') {
                // Erase vertex
                if (st.size() == 0u)
                    continue;
                unsigned int pos = magic.retrieve(1u, st.size());
                auto it = st.find_by_order(pos - 1); int id = *it;
                int siz = cvxhull.size();
                for (int i = 0; !rebuild && i < siz; i++)
                    if (cvxhull[i].id == id)
                        rebuild = true;
                st.erase(it); vis[id] = false; update = true;
                //cerr << "erase: #" << id << " x = " << arr[id].x << " y = " << arr[id].y << endl;
            } else if (ch == 'q') {
                // Query global minimum
                if (rebuild) {
                    vertices.clear(); rebuild = false; update = false;
                    for (int i = 1; i <= idPt; i++)
                        if (vis[i])
                            vertices.push_back(arr[i]);
                    convexHull(); vertices = cvxhull;
                } else if (update) {
                    update = false; int siz = vertices.size();
                    for (int i = 0; i < siz; i++) {
                        if (!vis[vertices[i].id]) {
                            swap(vertices[i], vertices[siz - 1]);
                            vertices.pop_back(); i--; siz--;
                        }
                    }
                    convexHull(); vertices = cvxhull;
                }

                pair<int, int> ret = make_pair(0, 0); long long int minv = LLONG_MAX;
                vertices = cvxhull; int siz = vertices.size();
                sort(vertices.begin(), vertices.end(), [](const Vertex & fst, const Vertex & snd) {
                    return fst.id < snd.id;
                });
                for (int i = 0; i < siz; i++) {
                    for (int j = i; j < siz; j++) {
                        long long int dp = dotProd(vertices[i], vertices[j]);
                        if (minv > dp)
                            minv = dp, ret = make_pair(vertices[i].id, vertices[j].id);
                    }
                }
                magic.submit(ret.first); magic.submit(ret.second);
                //cerr << "query: " << ret.first << " - " << ret.second << endl; 
            }
        }
        cout << magic.retrieveAns() << '\n';
    }

    return 0;
}