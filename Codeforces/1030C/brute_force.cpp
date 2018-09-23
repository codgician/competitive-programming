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

#define SIZE 110

int pfxSum[SIZE];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int len;
    cin >> len;
    string str;
    cin >> str;

    pfxSum[0] = 0;
    int pt = 1;
    for (auto it = str.begin(); it != str.end(); ++it)
    {
        pfxSum[pt] = pfxSum[pt - 1] + (*it - '0');
        pt++; 
    }

    bool ans = false;
    for (int i = 1; i < len; i++)
    {
        if (pfxSum[i] == 0)
        {
            if (pfxSum[len] == 0)
            {
                ans = true;
                break;
            }
            else
            {
                continue;
            }
        }

        if (pfxSum[len] % pfxSum[i] != 0)
            continue;

        bool cntAns = true;
        int lastMul = 1;
        for (int j = i + 1; j <= len; j++)
        {
            if (pfxSum[j] % pfxSum[i] == 0)
            {
                int cntMul = pfxSum[j] / pfxSum[i];
                if (cntMul <= lastMul + 1)
                    lastMul = cntMul;
                else
                {
                    cntAns = false;
                    break;
                }
            }
        }

        if (lastMul == 1)
        {
            cntAns = false;
        }

        if (cntAns)
        {
            ans = true;
            break;
        }
    }

    if (ans)
        cout << "YES" << endl;
    else
        cout << "NO" << endl;

    return 0;
}