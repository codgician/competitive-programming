#include <bits/stdc++.h>
using namespace std;

#define SIZE 200010

int arr[SIZE];
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int caseNum; cin >> caseNum;
    while (caseNum--) {
        int len; cin >> len;
        for (int i = 0; i < len; i++)
            cin >> arr[i], arr[i] /= 100;
        sort(arr + 0, arr + len, greater<int>());

        int x, a, y, b; long long int req;
        cin >> x >> a >> y >> b >> req;
        long long int lcm = 1ll * a * b / __gcd(a, b);
        if (x < y)
            swap(a, b), swap(x, y);

        int leftPt = 1, rightPt = len, ans = -1;
        while (leftPt <= rightPt) {
            int midPt = (leftPt + rightPt) >> 1;
            const auto check = [x, a, y, b, len, req, lcm](int num) {
                long long int cnt = 0; int lcmNum = num / lcm;
                for (int i = 0; i < min(num, lcmNum); i++)
                    cnt += 1ll * arr[i] * (x + y);
                int fstNum = num / a - lcmNum, sndNum = num / b - lcmNum;
                for (int i = lcmNum; i < min(num, lcmNum + fstNum); i++)
                    cnt += 1ll * arr[i] * x;
                for (int i = lcmNum + fstNum; i < min(num, lcmNum + fstNum + sndNum); i++)
                    cnt += 1ll * arr[i] * y;
                return cnt >= req;
            };
            check(midPt) ? rightPt = midPt - 1, ans = midPt : leftPt = midPt + 1;
        }

        cout << ans << '\n';
    }
 
    return 0;
}