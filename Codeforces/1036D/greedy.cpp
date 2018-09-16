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

#define SIZE 300010

long long int fstArr[SIZE], sndArr[SIZE];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    
    int fstLen, sndLen;
    cin >> fstLen;
    fstArr[0] = 0;
    for (int i = 1; i <= fstLen; i++)
    {
        cin >> fstArr[i];
        fstArr[i] += fstArr[i - 1];
    }
    cin >> sndLen;
    sndArr[0] = 0;
    for (int i = 1; i <= sndLen; i++)
    {
        cin >> sndArr[i];
        sndArr[i] += sndArr[i - 1];         
    }

    if (fstArr[fstLen] != sndArr[sndLen])
    {
        cout << -1 << endl;
        return 0;
    }

    int ans = 0;
    int fstPt = 1, sndPt = 1;
    while (fstPt <= fstLen && sndPt <= sndLen)
    {
        while (fstArr[fstPt] < sndArr[sndPt] && fstPt <= fstLen)
        {
            fstPt++;
        }
        while (sndArr[sndPt] < fstArr[fstPt] && sndPt <= sndLen)
        {
            sndPt++;
        }

        if (fstArr[fstPt] == sndArr[sndPt])
        {
            fstPt++;
            sndPt++;
            ans++;
        }
    }

    cout << ans << endl;
    return 0;
}