#include <bits/stdc++.h>
using namespace std;

#define SIZE 101
const int p = 19260817;

unordered_map<unsigned long long int, int> mp;
int arr[SIZE][2];

unsigned long long int vecHash(const vector<int> & v) {
    unsigned long long int ret = 0;
    for (const auto & i : v)
        ret = ret * p + i;
    return ret;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int len; cin >> len;
    for (int i = 0; i < len; i++) {
        unsigned int cnt; cin >> cnt;
        arr[i][0] = cnt >> 15;
        arr[i][1] = cnt & ((1 << 15) - 1);
    }

    const auto solve = [len]() {
        for (int st = 0; st < (1 << 15); st++) {
            vector<int> v;
            for (int i = 0; i < len; i++)
                v.push_back(__builtin_popcount(arr[i][0] ^ st));
            for (int i = 0; i < len - 1; i++)
                v[i] = v[i + 1] - v[i];
            v.pop_back();
            for (auto & i : v)
                i = -i;
            mp[vecHash(v)] = st;
        }

        for (int st = 0; st < (1 << 15); st++) {
            vector<int> v;
            for (int i = 0; i < len; i++)
                v.push_back(__builtin_popcount(arr[i][1] ^ st));
            for (int i = 0; i < len - 1; i++)
                v[i] = v[i + 1] - v[i];
            v.pop_back(); auto h = vecHash(v);
            if (mp.find(h) != mp.end())
                return (mp[h] << 15) | st;
        }
        
        return -1;
    };

    cout << solve() << '\n';
    return 0;
}