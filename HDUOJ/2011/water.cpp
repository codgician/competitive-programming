#include <iostream>
#include <cstdio>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    int caseNum;
    cin >> caseNum;
    for (int i = 0; i < caseNum; i++)
    {
        double ans = 0;
        int n;
        cin >> n;
        for (int j = 1; j <= n; j++)
        {
            if (j % 2 == 0)
                ans -= (double)1 / j;
            else
                ans += (double)1 / j;
        }
        printf("%.2lf\n", ans);
    }
    return 0;
}
