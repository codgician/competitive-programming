#include <bits/stdc++.h>
using namespace std;

#define SIZE 200010
#define BIT_SIZE 2000010

long long int bit[4][BIT_SIZE];

int lowbit(int x) {
    return x & -x;
}

void add(int id, int pos, long long int val) {
    pos++;
    for (int i = pos; i < BIT_SIZE; i += lowbit(i))
        bit[id][i] += val;
}

long long int prefixSum(int id, int pos) {
    long long int ret = 0; pos++;
    for (int i = pos; i > 0; i -= lowbit(i))
        ret += bit[id][i];
    return ret;
}

long long int rangeSum(int id, int qLeftPt, int qRightPt) {
    return prefixSum(id, qRightPt) - prefixSum(id, qLeftPt - 1);
}

class Rect {
public:
    int x, y;
    bool operator < (const Rect & snd) const {
        if (x != snd.x)
            return x < snd.x;
        return y < snd.y;
    }
};

Rect arr[SIZE]; int len, a, b;

void clear() {
    for (int i = 0; i < 4; i++)
        fill(bit[i] + 0, bit[i] + BIT_SIZE, 0);
}

void upd1(int pos, long long int op) {
    add(0, arr[pos].y, op * (a + arr[pos].x) * (b + arr[pos].y));
    add(1, arr[pos].y, op * (a + arr[pos].x));
    add(2, arr[pos].y, op * (b + arr[pos].y));
    add(3, arr[pos].y, op);
}

void upd2(int pos, long long int op) {
    add(0, arr[pos].y, op * (a + arr[pos].x) * (b - arr[pos].y));
    add(1, arr[pos].y, op * (a + arr[pos].x));
    add(2, arr[pos].y, op * (b - arr[pos].y));
    add(3, arr[pos].y, op);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    
    cin >> len >> a >> b;
    long long int tot = (long long int)len * (len - 1) / 2;
    for (int i = 0; i < len; i++)
        cin >> arr[i].x >> arr[i].y;

    sort(arr + 0, arr + len);
    long double ans = 0; int l;
    l = 0; clear();
    for (int r = 0; r < len; r++) {
        for (; l < r && arr[l].x < arr[r].x - a; l++)
            upd1(l, -1);
        // Query yi in [yr - b, yr]
        int lb = max(0, arr[r].y - b), ub = arr[r].y;
        ans += rangeSum(0, lb, ub) + (long double)arr[r].x * arr[r].y * rangeSum(3, lb, ub);
        ans -= (long double)arr[r].y * rangeSum(1, lb, ub) + (long double)arr[r].x * rangeSum(2, lb, ub);
        upd1(r, 1);
    }
    
    l = 0; clear();
    for (int r = 0; r < len; r++) {
        for (; l < r && arr[l].x < arr[r].x - a; l++)
            upd2(l, -1);
        // Query yi in [yr + 1, yr + b]
        int lb = arr[r].y + 1, ub = arr[r].y + b;
        ans += rangeSum(0, lb, ub) + (long double)arr[r].y * rangeSum(1, lb, ub);
        ans -= (long double)arr[r].x * rangeSum(2, lb, ub) + (long double)arr[r].x * arr[r].y * rangeSum(3, lb, ub);
        upd2(r, 1);
    }
    
    cout << fixed << setprecision(4) << (long double)ans / tot << '\n';
    return 0;
}