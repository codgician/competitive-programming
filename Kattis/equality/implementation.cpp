#include <bits/stdc++.h>
using namespace std;

class List {
public:
    bool isShuffle;
    vector<int> vec;

    void sorted() {
        isShuffle = false;
        sort(vec.begin(), vec.end());
    }

    void shuffle() {
        assert(vec.size() > 0);
        sort(vec.begin(), vec.end());
        isShuffle = vec.front() != vec.back();
    }

    void concat(const List & snd) {
        assert(!isShuffle && !snd.isShuffle);
        for (const auto & i : snd.vec)
            vec.push_back(i);
    }

    bool operator == (const List & snd) const {
        if (isShuffle != snd.isShuffle || vec.size() != snd.vec.size())
            return false;
        int siz = vec.size();
        for (int i = 0; i < siz; i++)
            if (vec[i] != snd.vec[i])
                return false;
        return true;
    }
};

#define FUNC_CONCAT 0
#define FUNC_SHUFFLE 1
#define FUNC_SORTED 2

int parseFunc(const string & str) {
    if (str[0] == 'c')
        return FUNC_CONCAT;
    if (str[1] == 'o')
        return FUNC_SORTED;
    if (str[1] == 'h')
        return FUNC_SHUFFLE;
    return -1;
}

vector<List> parse(const string & str) {
    int len = str.size(), cntPt = 0; vector<List> ret;
    while (cntPt < len) {
        const auto & ch = str[cntPt];
        // Parse function
        if (ch >= 'a' && ch <= 'z') {
            string buf;
            while (cntPt < len && str[cntPt] != '(')
                buf.push_back(str[cntPt]), cntPt++;
            int func = parseFunc(buf); cntPt++;
            assert(func != -1);
            if (func == FUNC_CONCAT) {
                continue;   // See everything as concat 
            } else {
                List l; auto & v = l.vec; int step = 1, val = 0; 
                while (cntPt < len && step > 0) {
                    if (str[cntPt] >= '0' && str[cntPt] <= '9') {
                        val = val * 10 + str[cntPt] - '0';
                    } else if (str[cntPt] == ',' || str[cntPt] == ']') {
                        if (val > 0)
                            v.push_back(val), val = 0;
                    } else if (str[cntPt] == '(') {
                        step++;
                    } else if (str[cntPt] == ')') {
                        step--;
                    }
                    cntPt++;
                }

                func == FUNC_SORTED ? l.sorted() : l.shuffle();
                ret.push_back(l);
            }
            continue;
        }
        // Parse List
        if (ch == '[') {
            List l; auto & v = l.vec; int val = 0;
            while (cntPt < len && str[cntPt] != ']') {
                if (str[cntPt] >= '0' && str[cntPt] <= '9')
                    val = val * 10 + str[cntPt] - '0';
                else if (str[cntPt] == ',')
                    v.push_back(val), val = 0;
                cntPt++;
            }
            v.push_back(val); l.isShuffle = false; 
            ret.push_back(l); cntPt++;
            continue;
        }
        cntPt++;
    }
    return ret;
}

void simplify(vector<List> & vec) {
    int siz = vec.size(), len = 0;
    for (int i = 1; i < siz; i++) {
        if (!vec[len].isShuffle && !vec[i].isShuffle)
            vec[len].concat(vec[i]);
        else
            vec[++len] = vec[i];
    }
    vec.erase(vec.begin() + len + 1, vec.end());
}

bool isEqual(const vector<List> & fst, const vector<List> & snd) {
    if (fst.size() != snd.size())
        return false;
    int siz = fst.size();
    for (int i = 0; i < siz; i++)
        if (!(fst[i] == snd[i]))
            return false;
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    string a, b; cin >> a >> b;
    auto va = parse(a), vb = parse(b);
    simplify(va); simplify(vb);
    cout << (isEqual(va, vb) ? "equal\n" : "not equal\n");

    return 0;
}
