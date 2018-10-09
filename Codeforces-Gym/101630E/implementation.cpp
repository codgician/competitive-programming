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

#define SIZE 1010

int arr[SIZE];
int ansArr[SIZE];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int num;
    while (cin >> num)
    {
        memset(arr, 0, sizeof(arr));
        bool ans = true;

        int uniNum = 0, ansPt = 0;
        for (int i = 0; i < num; i++)
        {
            int cnt;
            cin >> cnt;

            if (!ans)
                continue;

            if (cnt > 0)
            {
                arr[cnt]++;
            }
            else if (cnt < 0)
            {
                cnt *= -1;
                arr[cnt]--;
                if (arr[cnt] < 0)
                {
                    if (uniNum > 0)
                    {
                        ansArr[ansPt++] = cnt;
                        arr[cnt]++;
                        uniNum--;
                    }
                    else
                    {
                        ans = false;
                    }
                }
            }
            else if (cnt == 0)
            {
                uniNum++;
            }
        }

        if (ans)
        {
            cout << "Yes" << endl;
            for (int i = 0; i < ansPt + uniNum; i++)
            {
                if (i < ansPt)
                    cout << ansArr[i];
                else
                    cout << 1;

                if (i < ansPt + uniNum - 1)
                    cout << " ";
                else
                    cout << endl;
            }
        }
        else
        {
            cout << "No" << endl;
        }
    }

    return 0;
}