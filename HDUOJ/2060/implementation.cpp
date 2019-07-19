#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    int caseNum;
    cin >> caseNum;
    for (int t = 0; t < caseNum; t++)
    {
        int ballNum, cntScore, oppScore;
        cin >> ballNum >> cntScore >> oppScore;
        if (ballNum <= 6)
        {
            for (int i = 0, ballVal = 7; i < ballNum; i++, ballVal--)
                cntScore += ballVal;
        }
        else
        {
            cntScore += 8 * (ballNum - 6) + 27;
        }

        if (cntScore < oppScore)
            cout << "No" << endl;
        else
            cout << "Yes" << endl;
    }
    return 0;
}
