#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <string>
#include <cstring>
#include <iomanip>
#include <climits>
#include <stack>
#include <queue>
#include <vector>
#include <set>
#include <map>
#include <functional>
#include <iterator>
using namespace std;

#define SIZE 100010

int fstArr[SIZE][7], sndArr[SIZE][7];
long long int fstMax[128], sndMax[128];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int caseNum;
    cin >> caseNum;
    while (caseNum--)
    {
        int fstNum, sndNum, propNum;
        cin >> fstNum >> sndNum >> propNum;

        propNum += 2;

        for (int i = 0; i < fstNum; i++)
        {
            cin >> fstArr[i][0];
            fstArr[i][1] = 0;
            for (int j = 2; j < propNum; j++)
            {
                cin >> fstArr[i][j];
            }
        }

        for (int i = 0; i < sndNum; i++)
        {
            sndArr[i][0] = 0;
            cin >> sndArr[i][1];
            for (int j = 2; j < propNum; j++)
            {
                cin >> sndArr[i][j];
            }
        }

        for (int i = 0; i < (1 << propNum); i++)
        {
            fstMax[i] = LLONG_MIN;
            sndMax[i] = LLONG_MIN;
        }

        for (int t = 0; t < (1 << propNum); t++)
        {
            for (int i = 0; i < fstNum; i++)
            {
                long long int fstCnt = 0;
                for (int j = 0; j < propNum; j++)
                {
                    if (t & (1 << j))
                        fstCnt += fstArr[i][j];
                    else
                        fstCnt -= fstArr[i][j];
                }
                fstMax[t] = max(fstMax[t], fstCnt);
            }

            for (int i = 0; i < sndNum; i++)
            {
                long long int sndCnt = 0;
                for (int j = 0; j < propNum; j++)
                {
                    if (t & (1 << j))
                        sndCnt += sndArr[i][j];
                    else
                        sndCnt -= sndArr[i][j];
                }
                sndMax[t] = max(sndMax[t], sndCnt);
            }
        }

        long long int ans = LLONG_MIN;
        for (int i = 0; i < (1 << propNum); i++)
        {
            ans = max(ans, fstMax[i] + sndMax[(1 << propNum) - 1 - i]);
        }
        cout << ans << endl;
    }
    return 0;
}