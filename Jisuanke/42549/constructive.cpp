#include <bits/stdc++.h>
using namespace std;

#define SIZE 1010

vector<int> vecs[SIZE];
int dirs[2][2] = {0, 1, 1, 0};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    
    int num; cin >> num;
    for (int i = 2; i <= num; i += 2) {
        int len = num + 1 - i, x = 1, y = i, d = 0;
        vecs[len].push_back(y); 
        for (int t = 0; t < len; t++) {
            vecs[len].push_back(d == 0 ? x : y);
            x += dirs[0][d], y += dirs[1][d]; d ^= 1;
        }
        len--; vecs[len].push_back(vecs[len + 1].back());
        for (int t = 0; t < len; t++) {
            vecs[len].push_back(d == 0 ? x : y);
            x += dirs[0][d], y += dirs[1][d]; d ^= 1;
        }
    }

    for (int i = 1; i < num; i++) 
        for (int j = 0; j <= i; j++)
            cout << vecs[i][j] << (j == i ? '\n' : ' ');

    return 0;
}
