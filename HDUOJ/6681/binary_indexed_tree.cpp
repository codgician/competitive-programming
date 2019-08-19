#include <bits/stdc++.h>
using namespace std;

#define SIZE 100010

long long int bit[SIZE]; int lim;

int lowbit(int n) {
    return n & -n;
}

void add(int pos, int val) {
    pos++;
    for (int i = pos; i <= lim + 1; i += lowbit(i))
        bit[i] += val;
}

long long int prefixSum(int pos) {
    long long int ret = 0; pos++;
    for (int i = pos; i > 0; i -= lowbit(i))
        ret += bit[i];
    return ret;
}

long long int rangeSum(int qLeftPt, int qRightPt) {
    return prefixSum(qRightPt) - prefixSum(qLeftPt - 1);
}

class Node {
public:
    int x, y, dir;
    bool operator < (const Node & snd) const {
        return x < snd.x;
    }
};

Node arr[SIZE];

int conv(char ch) {
    if (ch == 'L')
        return 0;
    if (ch == 'R')
        return 1;
    if (ch == 'U')
        return 2;
    return 3;
}

vector<int> dsc;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int caseNum; cin >> caseNum;
    while (caseNum--) {
        dsc.clear();
        int row, column, len; cin >> row >> column >> len;
        for (int i = 0; i < len; i++) {
            cin >> arr[i].x >> arr[i].y;
            char ch; cin >> ch;
            arr[i].dir = conv(ch);
            dsc.push_back(arr[i].y);
        }

        sort(dsc.begin(), dsc.end());
        for (int i = 0; i < len; i++)
            arr[i].y = lower_bound(dsc.begin(), dsc.end(), arr[i].y) - dsc.begin();
        sort(arr + 0, arr + len);

        long long int ans = 1; lim = dsc.size() + 1;
        // x1 < x2, y1 > y2, d1 = 1, d2 = 2
        fill(bit + 0, bit + lim + 2, 0);
        for (int i = 0; i < len; i++) {
            if (arr[i].dir == 2)
                ans += rangeSum(arr[i].y, lim);
            if (arr[i].dir == 1)
                add(arr[i].y, 1);
        }

        // x1 < x2, y1 > y2, d1 = 3, d2 = 0
        fill(bit + 0, bit + lim + 2, 0);
        for (int i = 0; i < len; i++) {
            if (arr[i].dir == 0)
                ans += rangeSum(arr[i].y, lim);
            if (arr[i].dir == 3)
                add(arr[i].y, 1);
        }

        // x1 < x2, y1 < y2, d1 = 2, d2 = 0
        fill(bit + 0, bit + lim + 2, 0);
        for (int i = 0; i < len; i++) {
            if (arr[i].dir == 0)
                ans += prefixSum(arr[i].y);
            if (arr[i].dir == 2)
                add(arr[i].y, 1);
        }

        // x1 < x2, y1 < y2, d1 = 1, d2 = 3
        fill(bit + 0, bit + lim + 2, 0);
        for (int i = 0; i < len; i++) {
            if (arr[i].dir == 3)
                ans += prefixSum(arr[i].y);
            if (arr[i].dir == 1)
                add(arr[i].y, 1);
        }

        cout << ans << '\n';
    }

    return 0;
}