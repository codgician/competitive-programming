#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;

#define SIZE 200010

int arr[SIZE], pos[SIZE];
long long int bit1[SIZE], bit2[SIZE];

int lowbit(int x) {
    return x & -x;
}

void add(long long int * bit, int pos, int val) {
    for (int i = pos; i < SIZE; i += lowbit(i)) 
        bit[i] += val;
}

long long int prefixSum(long long int * bit, int pos) {
    long long int ret = 0;
    for (int i = pos; i > 0; i -= lowbit(i))
        ret += bit[i];
    return ret;
}

long long int rangeSum(long long int * bit, int l, int r) {
    return prefixSum(bit, r) - prefixSum(bit, l - 1);
}

long long int pprefixSum(int pos) {
    return (pos + 1) * prefixSum(bit1, pos) - prefixSum(bit2, pos);
}

long long int rangepSum(int l, int r) {
    return pprefixSum(r) - pprefixSum(l - 1);
}

__gnu_pbds::tree<
    int,
    __gnu_pbds::null_type,
    greater<int>,
    __gnu_pbds::rb_tree_tag,
    __gnu_pbds::tree_order_statistics_node_update
> st;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int len; cin >> len;
    for (int i = 1; i <= len; i++) 
        cin >> arr[i], pos[arr[i]] = i;
    
    long long int inv = 0;
    for (int t = 1; t <= len; t++) {
        inv += rangeSum(bit1, pos[t], len);
        add(bit1, pos[t], 1); add(bit2, pos[t], pos[t]);

        st.insert(pos[t]);
        int midPos = *st.find_by_order(st.size() >> 1);
        long long int midPfx = prefixSum(bit1, midPos);

        long long int l = pprefixSum(midPos - 1) - midPfx * (midPfx - 1) / 2;
        long long int r = 1ll * t * (len - midPos + 1) - rangepSum(midPos, len) - (t - midPfx) * (t - midPfx + 1) / 2;
        cout << inv + l + r << ' ';
    }

    cout << '\n';
    return 0;
}