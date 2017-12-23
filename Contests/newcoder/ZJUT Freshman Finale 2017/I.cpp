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
        int mstLife, sbLife, mstAttack, sbAttack;
        cin >> mstLife >> sbLife >> mstAttack >> sbAttack;
        int sbNeed = mstLife / sbAttack;
        if (mstLife % sbAttack > 0)
            sbNeed++;
        int mstNeed = sbLife / mstAttack;
        if (sbLife % mstAttack > 0)
            mstNeed++;
        if (mstNeed >= sbNeed)
            cout << "Yes" << endl;
        else
            cout << "No" << endl;
    }
    return 0;
}
