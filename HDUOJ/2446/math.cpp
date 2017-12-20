#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <string>
#include <iomanip>
#include <climits>
using namespace std;

long long int calc1(long long int n)
{
    if (n % 2 == 0)
    {
        return (n >> 1) * (n + 1) * (n + 2) / 3;
    }
    else
    {
        return ((n + 1) >> 1) * n * (n + 2) / 3;
    }
}

long long int calc2(long long int n)
{
    if (n % 2 == 0)
    {
        return (n >> 1) * (n + 1);
    }
    else
    {
        return ((n + 1) >> 1) * n;
    }
}

int main()
{
    ios::sync_with_stdio(false);
    int caseNum;
    cin >> caseNum;
    while (caseNum--)
    {
        long long int n;
        cin >> n;
        long long int tmp = cbrt(n) * cbrt(6);
        while (true)
        {
            if (calc1(tmp) >= n)
                break;
            tmp++;
        }
        long long int layer = tmp;
        long long int cntPos = n - calc1(tmp - 1);

        tmp = sqrt(cntPos) * sqrt(2);
        while (true)
        {
            if (calc2(tmp) >= cntPos)
                break;
            tmp++;
        }
        long long int row = tmp;
        long long int column = cntPos - calc2(tmp - 1);
        cout << layer << " " << row << " " << column << endl;
    }
    return 0;
}
