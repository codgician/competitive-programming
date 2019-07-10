#include <bits/stdc++.h>
using namespace std;

#define SIZE 550

long long int modArr[SIZE], cstArr[SIZE];
int equNum;

long long int extEuclid(long long int a, long long int b, long long int & x, long long int & y) {
    if (b == 0) {
        x = 1, y = 0;
        return a;
    }
    long long int gcd = extEuclid(b, a % b, x, y), tmp = x;
    x = y;
    y = tmp - y * (a / b);
    return gcd;
}

long long int crt() {
    long long int modProd = modArr[0], ans = cstArr[0];
    for (int i = 1; i < equNum; i++) {
        long long int x, y, a = modProd, b = modArr[i];
        long long int c = (cstArr[i] - ans % b + b) % b;
        long long int gcd = extEuclid(a, b, x, y), bg = b / gcd;

        if (c % gcd != 0)
            return -1;

        long long int cntAns = (c / gcd % bg * x % bg + bg) % bg;
        ans += modProd * cntAns;
        modProd *= bg;
    }

    return (ans % modProd + modProd) % modProd;
}

vector<int> vec[SIZE];
vector<pair<int, int> > tmp;
pair<int, int> pos[SIZE];
int arr[SIZE], chkPos[SIZE], chk[SIZE], vld[SIZE], len;

bool validate(int num) {
    for (int i = 0; i < len; i++) {
        int siz = vec[pos[i].first].size();
        int pt = vec[pos[i].first][(pos[i].second - num % siz + siz) % siz];
        vld[pt] = i;
        if (vld[pt] != chk[pt])
            return false;
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    while (cin >> len) {
        if (len == 0)
            break;

        for (int i = 0; i < len; i++) {
            cin >> arr[i]; arr[i]--;
            pos[i] = make_pair(-1, -1);
        }

        int permuNum = 0;
        for (int i = 0; i < len; i++) {
            if (pos[i].first != -1)
                continue;
            vec[permuNum].clear(); cstArr[permuNum] = -1;
            int cntPos = i;
            while (pos[cntPos].first == -1) {
                pos[cntPos] = make_pair(permuNum, vec[permuNum].size());
                vec[permuNum].push_back(cntPos);
                cntPos = arr[cntPos];
            }
            permuNum++;
        }

        for (int i = 0; i < len; i++) {
            cin >> chk[i]; chk[i]--;
            chkPos[chk[i]] = i;
        }

        bool hasAns = true;
        for (int i = 0; i < len && hasAns; i++) {
            int permuId = pos[chk[i]].first;
            if (cstArr[permuId] != -1)
                continue;
            modArr[permuId] = vec[permuId].size();
            cstArr[permuId] = pos[chk[i]].second;
        }

        equNum = permuNum;
        long long int ans = crt();
        cout << (validate(ans) ? ans : -1) << '\n';
    }

    return 0;
}