#include <bits/stdc++.h>
using namespace std;

#define SIZE 64

unsigned long long int binom[SIZE][SIZE];

void initBinom() {
    binom[0][0] = 1;
    for (int i = 1; i < SIZE; i++) {
        binom[i][0] = 1; binom[i][i] = 1;
        for (int j = 1; j < i; j++)
            binom[i][j] = binom[i - 1][j - 1] + binom[i - 1][j];
    }
}

unsigned long long int fastPow(unsigned long long int a, unsigned long long int n) {
    unsigned long long int ret = 1;
    while (n > 0) {
        if (n & 1)
            ret *= a;
        a *= a; n >>= 1;
    }
    return ret;
}

class Polyn {
public:
    vector<unsigned long long int> vec;
    Polyn(int siz = 0) { vec.resize(siz); }

    Polyn operator * (const Polyn & snd) const {
        Polyn ret(min(SIZE, (int)(vec.size() + snd.vec.size() - 1)));
        for (int i = 0; i < min(SIZE, (int)vec.size()); i++)
            for (int j = 0; j < min(SIZE - i, (int)snd.vec.size()); j++)
                ret.vec[i + j] += vec[i] * snd.vec[j];
        return ret;
    }

    Polyn xAdd(unsigned long long int inc) {
        Polyn ret(vec.size());
        for (int i = 0; i < (int)vec.size(); i++)
            for (int j = 0; j <= i; j++)
                ret.vec[j] += vec[i] * binom[i][j] * fastPow(inc, i - j);
        return ret;
    }
};

Polyn solve(unsigned long long int x) {
    if (x == 0) {
        Polyn ret; ret.vec.push_back(1);
        return ret;
    }

    if (x & 1) {
        Polyn qaq; 
        qaq.vec.push_back((x << 1) - 1);
        qaq.vec.push_back(2);
        return qaq * solve(x - 1);
    }

    auto ret = solve(x >> 1);
    return ret * ret.xAdd(x >> 1);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    initBinom();

    unsigned long long int num, ans = 1; cin >> num;
    while (num > 1)
        num = (num + 1) >> 1, ans *= solve(num).vec[0];
    cout << ans << '\n';

    return 0;
}