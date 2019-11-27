#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;

#define SIZE 200010

class Query {
public:
    int id, len, pos;
    bool operator < (const Query & snd) const {
        return len > snd.len;
    }
};

Query ques[SIZE];
int arr[SIZE], ans[SIZE];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int len; cin >> len;
    priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > pq;
    __gnu_pbds::tree<
        pair<int, int>,
        __gnu_pbds::null_type,
        less<pair<int, int> >,
        __gnu_pbds::rb_tree_tag,
        __gnu_pbds::tree_order_statistics_node_update
    > st;
    for (int i = 0; i < len; i++) {
        cin >> arr[i]; pq.push(make_pair(arr[i], -i));
        st.insert(make_pair(i, arr[i]));
    }

    int qNum; cin >> qNum;
    for (int i = 0; i < qNum; i++)
        cin >> ques[i].len >> ques[i].pos, ques[i].pos--, ques[i].id = i;
    sort(ques + 0, ques + qNum);

    for (int i = 0; i < qNum; i++) {
        while ((int)st.size() > ques[i].len) {
            auto tp = pq.top(); pq.pop(); 
            st.erase(st.lower_bound(make_pair(-tp.second, -1)));
        }
        ans[ques[i].id] = st.find_by_order(ques[i].pos) -> second;
    }

    for (int i = 0; i < qNum; i++)
        cout << ans[i] << '\n';
    return 0;
}