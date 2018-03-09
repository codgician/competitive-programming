#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <string>
#include <iomanip>
#include <climits>
#include <vector>
#include <queue>
#include <set>
#include <map>
#define SIZE 1000010
using namespace std;

int fstArr[SIZE], sndArr[SIZE];

int main()
{
    ios::sync_with_stdio(false);
    int fstNum, sndNum;
    cin >> fstNum >> sndNum;

    for (int i = 0; i < fstNum; i++)
    {
        cin >> fstArr[i];
    }
    for (int i = 0; i < sndNum; i++)
    {
        cin >> sndArr[i];
    }

    int ans = 0;
    int fstPt = 0, sndPt = 0;
    int fstSum = 0, sndSum = 0;
    while (fstPt < fstNum && sndPt < sndNum)
    {
        if (fstSum > sndSum)
        {
            sndSum += sndArr[sndPt++];
        }
        else if (fstSum < sndSum)
        {
            fstSum += fstArr[fstPt++];
        }

        if (fstSum == sndSum)
        {
            if (fstSum != 0)
            {
                ans++;
                sndSum = 0;
            }
            fstSum = fstArr[fstPt++];
        }
    }

    while (fstPt < fstNum)
    {
        fstSum += fstArr[fstPt++];
        if (fstSum == sndSum)
        {
            ans++;
            break;
        }
    }

    while (sndPt < sndNum)
    {
        sndSum += sndArr[sndPt++];
        if (fstSum == sndSum)
        {
            ans++;
            break;
        }
    }

    cout << ans << endl;
    return 0;
}
