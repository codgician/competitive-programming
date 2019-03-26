#include <bits/stdc++.h>
using namespace std;

#define SIZE 1000010

set<long long int> st;
int arr[SIZE][3];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int n;
    cin >> n;
    for (int i = 2; i <= 3 * n + 1; i++)
        st.insert(i);

    for (long long int a = n + 1; a >= 2; a--) {
        st.erase(st.begin());
        long long int c = *st.rbegin();
        st.erase(prev(st.end()));

        auto it = st.lower_bound(sqrt(c * c - a * a) + 1);
        if (it == st.begin()) {
            cout << -1 << endl;
            return 0;
        }
        it = prev(it);
        if (*it * (*it) == c * c - a * a) {
            if (it == st.begin()) {
                cout << -1 << endl;
                return 0;
            }
            it = prev(it);
        }

        long long int b = *it;
        st.erase(it);
        arr[a - 2][0] = a, arr[a - 2][1] = b, arr[a - 2][2] = c;
    }

    for (int i = 0; i < n; i++) {
        cout << arr[i][0] << " " << arr[i][1] << " " << arr[i][2] << "\n";
    }

    return 0;
}