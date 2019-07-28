#include <bits/stdc++.h>
using namespace std;

#define SIZE 9
#define STATE_SIZE 19683

class Frac {
public:
    int x, y;

    void simplify() {
        while (x != 0 && !(x & 1))
            x >>= 1, y >>= 1;
    }

    bool operator == (const Frac & snd) const {
        return x == snd.x && y == snd.y;
    }
    bool operator < (const Frac & snd) const {
        return x * snd.y < y * snd.x;
    }
    bool operator <= (const Frac & snd) const {
        return *this < snd || *this == snd;
    }

    Frac operator + (const Frac & snd) const {
        int y1 = max(y, snd.y);
        int x1 = x * (y1 / y) + snd.x * (y1 / snd.y);
        Frac ret = {x1, y1}; ret.simplify();
        return ret;
    }

    Frac operator >> (const int & snd) const {
        Frac ret = *this;
        ret.y <<= snd;
        ret.simplify();
        return ret;
    }
};

Frac surreal[STATE_SIZE];
const Frac inf = {0, -1};

int cnt[9], nxt[9];

int id(char ch) {
    return ch == '.' || ch == '#' ? 0 : ch == 'O' ? 1 : 2;
}

int nxtst() {
    int ret = 0;
    for (int i = 0; i < 9; i++)
        ret = ret * 3 + nxt[i];
    return ret;
}

void initcnt(int st) {
    for (int i = 8; i >= 0; i--)
        cnt[i] = st % 3, st /= 3;
}

void banIt(int pos) {
    nxt[pos] = 0;
}

void banLeftRight(int pos) {
    int x = pos / 3;
    if (x > 0)
        banIt(pos - 3);
    if (x < 2)
        banIt(pos + 3);
}

void banUpDown(int pos) {
    int y = pos % 3;
    if (y > 0)
        banIt(pos - 1);
    if (y < 2)
        banIt(pos + 1);
}

void updMax(Frac & cnt) {
    Frac qaq = surreal[nxtst()];
    if (cnt == inf || cnt < qaq)
        cnt = qaq;
}

void updMin(Frac & cnt) {
    Frac qaq = surreal[nxtst()];
    if (cnt == inf || qaq < cnt)
        cnt = qaq;
}

void init() {
    for (int st = 0; st < STATE_SIZE; st++) {
        initcnt(st); 
        
        Frac leftMax = inf, rightMin = inf;
        for (int i = 0; i < 9; i++) {
            if (cnt[i] == 1) {   // White chess
                // Ban left and right
                copy(cnt + 0, cnt + 9, nxt + 0);
                banIt(i); banLeftRight(i);
                updMax(leftMax);

                // Ban up and down
                copy(cnt + 0, cnt + 9, nxt + 0);
                banIt(i); banUpDown(i);
                updMax(leftMax);

                // Ban both
                copy(cnt + 0, cnt + 9, nxt + 0);
                banIt(i); banUpDown(i); banLeftRight(i);
                updMax(leftMax);
            } else if (cnt[i] == 2) {   // Black chess
                copy(cnt + 0, cnt + 9, nxt + 0);
                banIt(i); updMin(rightMin);
            }
        }

        if (leftMax == inf && rightMin == inf) {
            surreal[st] = Frac{0, 1};
        } else if (leftMax == inf) {
            surreal[st] = Frac{rightMin.x - 1 , 1};
        } else if (rightMin == inf) {
            surreal[st] = Frac{leftMax.x + 1, 1};
        } else {
            Frac l = inf, r = inf, ret = Frac{0, 1};
            while (rightMin <= ret || ret <= leftMax) {
                if (rightMin <= ret) {
                    r = ret;
                    if (l == inf)
                        ret.x -= 1;
                    else
                        ret = (l + r) >> 1;
                } else {
                    l = ret;
                    if (r == inf)
                        ret.x += 1;
                    else
                        ret = (l + r) >> 1;
                }
            }
            surreal[st] = ret;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    init();
    int caseNum; cin >> caseNum;
    while (caseNum--) {
        int num, ret = 0; cin >> num;
        while (num--) {
            for (int i = 0; i < 3; i++) {
                string buf; cin >> buf;
                for (int j = 0; j < 5; j += 2)
                    nxt[i * 3 + (j >> 1)] = id(buf[j]);
            }
            int st = nxtst();
            ret += (surreal[st].x * (256 / surreal[st].y));
        }

        cout << (ret == 0 ? "Second\n" : ret > 0 ? "Alice\n" : "Bob\n");
    }

    return 0;
}