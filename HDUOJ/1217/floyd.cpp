#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <string>
#include <cstring>
#include <iomanip>
#include <climits>
#include <vector>
#include <queue>
#include <set>
#include <map>
#define SIZE 31
using namespace std;

double arr[SIZE][SIZE];

map<string, int> mp;

int main()
{
    ios::sync_with_stdio(false);
    int currencyNum, caseId = 1;
    while (cin >> currencyNum)
    {
        if (currencyNum == 0)
            break;

        mp.clear();
        for (int i = 0; i < currencyNum; i++)
        {
            string str;
            cin >> str;
            mp[str] = i;
        }

        for (int i = 0; i < currencyNum; i++)
        {
            for (int j = 0; j < currencyNum; j++)
            {
                if (i == j)
                {
                    arr[i][j] = 1.0;
                }
                else
                {
                    arr[i][j] = 0.0;
                }
            }
        }

        int edgeNum;
        cin >> edgeNum;
        for (int i = 0; i < edgeNum; i++)
        {
            string from, to;
            double rate;
            cin >> from >> rate >> to;
            arr[mp[from]][mp[to]] = rate;
        }

        for (int k = 0; k < currencyNum; k++)
        {
            for (int i = 0; i < currencyNum; i++)
            {
                for (int j = 0; j < currencyNum; j++)
                {
                    arr[i][j] = max(arr[i][j], arr[i][k] * arr[k][j]);
                }
            }
        }

        bool ans = false;
        for (int i = 0; i < currencyNum; i++)
        {
            if (arr[i][i] > 1)
            {
                ans = true;
                break;
            }
        }

        cout << "Case " << caseId++ << ": ";
        if (ans)
            cout << "Yes" << endl;
        else
            cout << "No" << endl;
    }
    return 0;
}
