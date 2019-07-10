#include <iostream>
using namespace std;

#define SIZE 1010

int arr[SIZE], cnt[SIZE], nxt[SIZE], len;

bool equal() {
    for (int i = 0; i < len; i++)
        if (arr[i] != cnt[i])
            return false;
    return true;
}

void iterate() {
    for (int i = 0; i < len; i++)
        nxt[i] = cnt[cnt[i]];
    copy(nxt + 0, nxt + len, cnt + 0);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int transNum;
    while (cin >> len >> transNum) {
        for (int i = 0; i < len; i++) {
            cin >> arr[i]; arr[i]--;
            cnt[i] = arr[i];
        }

        int cycleLen = 1; iterate();
        while (!equal()) {
            iterate(); cycleLen++;
        }

        int rem = cycleLen - transNum % cycleLen;
        while (rem) {
            iterate(); rem--;
        }

        for (int i = 0; i < len; i++)
            cout << cnt[i] + 1 << '\n';
    }

    return 0;
}