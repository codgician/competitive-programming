#include <bits/stdc++.h>
using namespace std;
 
#define SIZE 7010

class Node {
public:
    long long int mask, val; 
    int num;
    bool operator < (const Node & snd) const {
        return mask < snd.mask;
    }
};
 
Node arr[SIZE];
bool mp[SIZE][SIZE];
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
 
    int len; cin >> len;
    for (int i = 0; i < len; i++)
        cin >> arr[i].mask, arr[i].num = 1;
    for (int i = 0; i < len; i++)
        cin >> arr[i].val;
    sort(arr + 0, arr + len);
    int pt = 0;
    for (int i = 1; i < len; i++)
        if (arr[pt].mask == arr[i].mask)
            arr[pt].val += arr[i].val, arr[pt].num += arr[i].num;
        else
            arr[++pt] = arr[i];
    len = pt + 1;

    vector<long long int> vec; long long int ans = 0;
    for (int i = 0; i < len; i++)
        if (arr[i].num > 1)
            vec.push_back(arr[i].mask), ans += arr[i].val;
    for (int i = 0; i < len; i++) {
        if (arr[i].num > 1)
            continue;
        auto check = [i, vec]() {
            for (const auto & v : vec)
                if ((v & arr[i].mask) == arr[i].mask)
                    return true;
            return false;
        };
        ans += check() ? arr[i].val : 0;
    }

    cout << ans << '\n';
    return 0;
}