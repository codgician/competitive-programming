#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <string>
#include <iomanip>
#define SIZE 501
using namespace std;

bool arr[SIZE][SIZE], used[SIZE];
int boy[SIZE];  // girlIndex of boy i.
int girlNum, boyNum;

bool canFind(int n)
{
    for (int i = 0; i < boyNum; i++)
    {
        if (arr[n][i] && !used[i])
        {
            used[i] = true;
            if (boy[i] == -1 || canFind(boy[i]))
            {
                boy[i] = n;
                return true;
            }
        }
    }
    return false;
}

int main()
{
    ios::sync_with_stdio(false);
    int possComb;
    while (cin >> possComb)
    {
        if (possComb == 0)
            break;

        cin >> girlNum >> boyNum;
        memset(arr, false, sizeof(arr));
        for (int i = 0; i < boyNum; i++)
            boy[i] = -1;

        for (int i = 0; i < possComb; i++)
        {
            int girl, boy;
            cin >> girl >> boy;
            arr[girl - 1][boy - 1] = true;
        }

        int ans = 0;
        for (int i = 0; i < girlNum; i++)
        {
            memset(used, false, sizeof(used));
            if (canFind(i))
                ans++;
        }

        cout << ans << endl;
    }
    return 0;
}
