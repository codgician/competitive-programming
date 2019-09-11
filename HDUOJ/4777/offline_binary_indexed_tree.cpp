#include <bits/stdc++.h>
using namespace std;

#define SIZE 200010

class Query {
public:
    int id, x, y;
    bool operator < (const Query & snd) const {
        if (x != snd.x)
            return x > snd.x;
        if (y != snd.y)
            return y < snd.y;
        return id < snd.id;
    }
};

Query ques[SIZE << 2];
int arr[SIZE], ans[SIZE], pos[SIZE], len;
int bit[SIZE];

int lowbit(int n) {
    return n & -n;
}

void add(int pos, int val) {
    pos += 2;
    for (int i = pos; i <= len + 2; i += lowbit(i))
        bit[i] += val;
}

int prefixSum(int pos) {
    int ret = 0; pos += 2;
    for (int i = pos; i > 0; i -= lowbit(i))
        ret += bit[i];
    return ret;
}

int primes[SIZE], minFac[SIZE], primesPt;

pair<int, int> bounds[SIZE];

void initPrimes() {
    memset(minFac, 0, sizeof(minFac)); primesPt = 0;
    for (int i = 2; i < SIZE; i++) {
        if (minFac[i] == 0) 
            minFac[i] = i, primes[primesPt++] = i;
        for (int j = 0; j < primesPt && primes[j] <= min(minFac[i], (SIZE - 1) / i); j++)
            minFac[i * primes[j]] = primes[j];
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int qNum; initPrimes();
    while (cin >> len >> qNum) {
        if (len == 0 && qNum == 0)
            break;
        for (int i = 0; i < len; i++)
            cin >> arr[i], bounds[i] = make_pair(-1, len);
        // Left
        fill(pos + 0, pos + SIZE, -1);
        for (int i = 0; i < len; i++) {
            int cnt = arr[i];
            while (cnt > 1) {
                int p = minFac[cnt]; cnt /= p;
                while (cnt > 1 && minFac[cnt] == p)
                    cnt /= p;
                bounds[i].first = max(bounds[i].first, pos[p]), pos[p] = i;
            }
        }
        // Right
        fill(pos + 0, pos + SIZE, len);
        for (int i = len - 1; i >= 0; i--) {
            int cnt = arr[i];
            while (cnt > 1) {
                int p = minFac[cnt]; cnt /= p;
                while (cnt > 1 && minFac[cnt] == p)
                    cnt /= p;
                bounds[i].second = min(bounds[i].second, pos[p]), pos[p] = i;
            }
        }
        
        int quesPt = 0;
        for (int i = 0; i < len; i++) {
            // bounds[i].first++, bounds[i].second--;
            ques[quesPt++] = {-1, bounds[i].first, i};
            ques[quesPt++] = {-1, i, bounds[i].second};
            ques[quesPt++] = {-2, bounds[i].first, bounds[i].second};
        }

        for (int i = 0; i < qNum; i++) {
            int qLeftPt, qRightPt; cin >> qLeftPt >> qRightPt;
            qLeftPt--; qRightPt--; ans[i] = qRightPt - qLeftPt + 1;
            ques[quesPt++] = {i, qLeftPt, qRightPt};
        }

        fill(bit + 0, bit + len + 3, 0);
        sort(ques + 0, ques + quesPt);

        for (int i = 0; i < quesPt; i++) {
            const auto & q = ques[i];
            if (q.id < 0) {
                // Modify
                add(q.y, q.id == -1 ? 1 : -1);
            } else {
                // Query
                ans[q.id] = q.y - q.x + 1 - prefixSum(q.y);
            }
        }

        for (int i = 0; i < qNum; i++)
            cout << ans[i] << '\n';
    }

    return 0;
}