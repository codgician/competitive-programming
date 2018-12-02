#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <string>
#include <iomanip>
#include <climits>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    int caseNum;
    cin >> caseNum;
    while (caseNum--)
    {
        double a, b, c;
        cin >> a >> b >> c;
        double prev = a + b + c;
        double cnt = 1.0 / (1.0 / b + 1.0 / prev) + a + c;
        while (fabs(prev - cnt) > 1e-5)
        {
            prev = cnt;
            cnt = 1.0 / (1.0 / b + 1.0 / prev) + a + c;
        }
        cout << fixed << setprecision(2) << cnt << endl;
    }
    return 0;
}
