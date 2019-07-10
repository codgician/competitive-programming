#include <iostream>
using namespace std;

#define SIZE 1010

int arr[SIZE];
bool vis[SIZE];

long long int gcd(long long int fst, long long int snd) {
    return snd == 0 ? fst : gcd(snd, fst % snd);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int len;
    while (cin >> len) {
        for (int i = 0; i < len; i++) {
            cin >> arr[i]; arr[i]--;
            vis[i] = false;
        }

        long long int ans = 1;
        for (int i = 0; i < len; i++) {
            if (vis[i])
                continue;
            int cntPos = i; long long int cntSiz = 0;
            while (!vis[cntPos]) {
                vis[cntPos] = true;
                cntSiz++; cntPos = arr[cntPos];
            }
            ans = ans * cntSiz / gcd(ans, cntSiz);
        }

        cout << ans << '\n';
    }

    return 0;
}