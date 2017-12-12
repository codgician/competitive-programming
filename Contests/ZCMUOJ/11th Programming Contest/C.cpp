#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <string>
#include <iomanip>
#include <climits>
#define SIZE 100001
using namespace std;

int zPos[SIZE], zPosPt;
int cPos[SIZE], cPosPt;
int mPos[SIZE], mPosPt;

int main()
{
    ios::sync_with_stdio(false);
    string str;
    while (cin >> str)
    {
        zPosPt = 0;
        cPosPt = 0;
        mPosPt = 0;
        int minDel = SIZE;
        for (int i = 0; i < str.length(); i++)
        {
            if (str[i] == 'z')
                zPos[zPosPt++] = i;
            else if (str[i] == 'c')
                cPos[cPosPt++] = i;
            else if (str[i] == 'm')
                mPos[mPosPt++] = i;
            else if (str[i] == 'u')
            {
                for (int j = zPosPt - 1; j >= 0; j--)
                {
                    bool isValid = false;
                    for (int k = cPosPt - 1; cPos[k] > zPos[j]; k--)
                    {
                        if (cPos[k] < mPos[mPosPt - 1])
                            isValid = true;
                    }
                    if (isValid)
                    {
                        minDel = min(minDel, i - zPos[j] - 3);
                        break;
                    }
                }
            }
        }
        if (minDel == SIZE)
            cout << -1 << endl;
        else
            cout << minDel << endl;
    }
    return 0;
}
