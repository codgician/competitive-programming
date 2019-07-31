#include <bits/stdc++.h>
using namespace std;

#define SIZE 100010

vector<int> vec[SIZE];
int len, k;

bool check() {
    if (len % k != 0 || len / k == 1)
        return false;
    long long int sum = 1ll * len * (len + 1) / 2;
    if (sum % k != 0)
        return false;
    return true;
}

void three() {
    int cntLen = k * 3; long long int tot = 1ll * (cntLen + 1) * cntLen / 2;
    tot /= k; 
    for (int i = 0; i < k; i++)
        vec[i].push_back(k * 3 - i);
    int midPt = k >> 1; vec[midPt].push_back(1);
    for (int i = midPt - 1; i >= 0; i--)
        vec[i].push_back(midPt - i + 1);
    for (int i = midPt + 1; i < k; i++)
        vec[i].push_back(k - (i - midPt) + 1);
    for (int i = 0; i < k; i++)
        vec[i].push_back(tot - vec[i][0] - vec[i][1]);
}

void brush(int startPt) {
    for (int i = startPt; i <= len; i += (k << 1)) {
        for (int j = 0; j < k; j++)
            vec[j].push_back(i + j);
        for (int j = 0; j < k; j++)
            vec[j].push_back(i + (k << 1) - j - 1);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int caseNum; cin >> caseNum;
    while (caseNum--) {
        cin >> len >> k;
        if (len == 1 && k == 1) {
            cout << "yes\n1\n";
            continue;
        }

        if (!check()) {
            cout << "no\n";
            continue;
        }
        cout << "yes\n";

        for (int i = 0; i < k; i++)
            vec[i].clear();

        int rem = len / k; 
        if (rem & 1)
            three(), brush(3 * k + 1);
        else
            brush(1);
        
        for (int i = 0; i < k; i++)
            for (int j = 0; j < rem; j++)
                cout << vec[i][j] << (j < rem - 1 ? ' ' : '\n');
    }

    return 0;
}