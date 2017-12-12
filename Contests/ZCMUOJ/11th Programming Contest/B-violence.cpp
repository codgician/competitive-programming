#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <string>
#include <iomanip>
#include <climits>
using namespace std;

inline unsigned long long int calc(unsigned long long int k)
{
    return ((k * k * k) << 2) + (k << 1);
}

int main()
{
    ios::sync_with_stdio(false);
    int caseNum;
    cin >> caseNum;
    int maxPt = 0;
    for (int t = 0; t < caseNum; t++)
    {
        unsigned long long int n;
        cin >> n;
        int pt = cbrt(n / 4.0);
        while (calc(pt) < n)
        {
            pt++;
        }
        cout << calc(pt) << endl;
    }
    return 0;
}
