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
#include <map>
#include <set>
#include <stack>
#include <functional>
#include <iterator>
using namespace std;

int arr[2][26];

int main()
{
    ios::sync_with_stdio(false);
    int caseNum;
    cin >> caseNum;
    while (caseNum--)
    {
        memset(arr, 0, sizeof(arr));
        string str;
        cin >> str;

        for (int i = 0; i < (int)str.length(); i++)
        {
            arr[i & 1][str[i] - 'a']++;
        }

        int maxNum1 = -1, maxCh1 = -1;
        for (int i = 0; i < 26; i++)
        {
            if (arr[0][i] > maxNum1)
            {
                maxNum1 = arr[0][i];
                maxCh1 = i;
            }
        }

        int maxNum2 = -1, maxCh2 = -1;
        for (int i = 0; i < 26; i++)
        {
            if (arr[1][i] > maxNum2)
            {
                maxNum2 = arr[1][i];
                maxCh2 = i;
            }
        }

        int ans = 0;
        for (int i = 0; i < (int)str.length(); i++)
        {
            if ((!(i & 1) && str[i] - 'a' != maxCh1) || ((i & 1) && str[i] - 'a' != maxCh2))
            {
                ans++;
            }
        }

        cout << ans << endl;
    }
    return 0;
}
