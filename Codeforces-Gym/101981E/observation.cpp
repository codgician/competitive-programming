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
#include <cassert>
using namespace std;

#define SIZE 1000010

string str[2];
int arr[2][SIZE], arrPt[2];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int len, k;
    while (cin >> len >> k)
    {
        memset(arr, 0, sizeof(arr));
        cin >> str[0] >> str[1];

        for (int t = 0; t < 2; t++)
        {
            int strPt = 0;
            char prevVal = '0';
            while (strPt < len)
            {
                if (prevVal != str[t][strPt])
                {
                    prevVal = str[t][strPt];
                    arr[t][arrPt[t]] %= k;

                    if (arrPt[t] > 0 && arr[t][arrPt[t]] == 0)
                        arrPt[t]--;
                    else
                        arrPt[t]++;
                }
                arr[t][arrPt[t]]++;
                strPt++;
            }

            arr[t][arrPt[t]] %= k;
            while (arrPt[t] > 0 && arr[t][arrPt[t]] == 0)
                arrPt[t]--;
            if (arr[t][arrPt[t]] > 0)
                arrPt[t]++;
        }

        bool ans = arrPt[0] == arrPt[1];
        for (int i = 0; ans && i < arrPt[0]; i++)
            if (arr[0][i] != arr[1][i])
                ans = false;
        if (ans)
            cout << "Yes" << endl;
        else
            cout << "No" << endl;
    }

    return 0;
}