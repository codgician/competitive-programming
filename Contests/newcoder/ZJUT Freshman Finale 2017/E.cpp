#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <string>
#include <iomanip>
#include <climits>
#define SIZE 200001
using namespace std;

int a[SIZE], b[SIZE];

int main()
{
    ios::sync_with_stdio(false);
    int caseNum;
    cin >> caseNum;
    while (caseNum--)
    {
        int aLen, bLen, k;
        cin >> aLen >> bLen >> k;
        for (int i = 0; i < aLen; i++)
        {
            cin >> a[i];
        }

        for (int i = 0; i < bLen; i++)
        {
            cin >> b[i];
        }

        int ans = 0;
        for (int i = 0; i < aLen - bLen + 1; i++)
        {
            bool flag = true;
            int base = (a[i] + b[0]) % k;
            for (int j = 1; j < bLen; j++)
            {
                if ((a[i + j] + b[j]) % k != base)
                {
                    flag = false;
                    break;
                }
            }
            if (flag)
                ans++;
        }

        cout << ans << endl;
    }
    return 0;
}
