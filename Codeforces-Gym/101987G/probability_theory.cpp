#include <bits/stdc++.h>
using namespace std;
 
#define SIZE 21
 
class Case {
public:
    int id; double prob;
    bool operator < (const Case & snd) const {
        if (prob != snd.prob)
            return prob < snd.prob;
        return id < snd.id; 
    }
};
 
Case arr[SIZE];
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
 
    int len; cin >> len;
    for (int i = 0; i < len; i++) {
        double s, w[3]; cin >> s;
        for (int j = 0; j < 3; j++)
            cin >> w[j];
        const auto solve = [s, w]() {
            double prob = 0;
            for (int i = 0; i < 3; i++) {
                for (int j = i + 1; j < 3; j++) {
                    prob += (w[i] * w[i] / 2 +  w[i] * (s - w[i] - w[j])) * w[j];
                    prob += w[i] * w[j] * w[j] / 2;
                    prob += (w[j] * w[j] / 2 +  w[j] * (s - w[j] - w[i])) * w[i];
                    prob += w[j] * w[i] * w[i] / 2;
                }
            }
            return prob / (s * s * s);
        };
        arr[i].id = i; arr[i].prob = solve();
    }
 
    sort(arr + 0, arr + len);
    for (int i = 0; i < len; i++)
        cout << arr[i].id + 1 << ' ';
    cout << '\n';
    return 0;
}