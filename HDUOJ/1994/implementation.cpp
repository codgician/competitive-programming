#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <iomanip>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    int caseNum;
    cin >> caseNum;
    for (int t = 0; t < caseNum; t++)
    {
        double original, hasSaved, currentRate, fixedRate, iFixedRate;
        cin >> original >> hasSaved >> currentRate >> fixedRate >> iFixedRate;
        printf("%.1f\n", original * (1 + currentRate / 100 * hasSaved / 365) * (1 + iFixedRate / 100));
        printf("%.1f\n", original * (1 + fixedRate / 100 * (hasSaved / 365 + 1)));
    }
    return 0;
}
