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

#define SIZE 101

char arr[SIZE];

int main()
{
    ios::sync_with_stdio(false);
    int avaNum, useNum;
    cin >> avaNum >> useNum;

    for (int i = 0; i < avaNum; i++)
    {
        cin >> arr[i];
    }

    sort(arr + 0, arr + avaNum);

    int cntWeight = 0, cntNum = 0;
    char lastAlphabet = -1;
    for (int i = 0; i < avaNum; i++)
    {
        if (arr[i] - lastAlphabet > 1)
        {
            cntWeight += arr[i] - 'a' + 1;
            cntNum++;
            lastAlphabet = arr[i];
            if (cntNum == useNum)
                break;
        }
    }

    if (cntNum < useNum)
        cout << -1 << endl;
    else
        cout << cntWeight << endl;

    return 0;
}