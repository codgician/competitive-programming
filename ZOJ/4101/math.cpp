#include <bits/stdc++.h>
using namespace std;

#define SIZE 200020

int arr[SIZE];
vector<long long int> fac;
map<long long int, int> mp;

long long int combN2(int num) {
    return 1ll * num * (num - 1) / 2;
}

int main() {
    int caseNum;
    scanf("%d", &caseNum);
    while (caseNum--) {
        int len; long long int x, y;
        scanf("%d%lld%lld", &len, &x, &y);
        long long int x1 = 0, y1 = 0;
        for (int i = 1; i <= len; i++) {
            scanf("%d", arr + i);
            x1 += 1ll * i * arr[i];
            y1 += 1ll * i * arr[i] * arr[i];
        }

        long long int dx = x1 - x, dy = y1 - y;

        if (dx == 0) {
            if (dy != 0) {
                printf("0\n");
                continue;
            }
            
            mp.clear();
            for (int i = 1; i <= len; i++)
                mp[arr[i]]++;
            long long int ans = 0;
            for (auto p : mp)
                ans += combN2(p.second);
            printf("%lld\n", ans);
            continue;
        }

        long long int sum = dy / dx;

        if (sum <= 0 || dy % dx != 0) {
            printf("0\n");
            continue;
        }

        fac.clear(); long long int cnt = llabs(dx);
        for (long long int i = 1; i * i <= cnt; i++) {
            if (cnt % i == 0) {
                fac.push_back(i);
                if (i * i != cnt)
                    fac.push_back(cnt / i);
            }
        }

        long long int ans = 0;
        for (auto dk : fac) {
            long long int da = dx / dk;
            for (int i = dk + 1; i <= len; i++) {
                if (arr[i] + arr[i - dk] == sum && arr[i] - arr[i - dk] == da) {
                    ans++;
                }
            } 
        }
        printf("%lld\n", ans);
    }

    return 0;
}