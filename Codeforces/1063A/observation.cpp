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

int arr[26];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int len;
    while (cin >> len)
    {
        memset(arr, 0, sizeof(arr));

        for (int i = 0; i < len; i++)
        {
            char ch;
            cin >> ch;
            arr[ch - 'a']++;
        }

        for (int i = 0; i < 26; i++)
        {
            char ch = 'a' + i;
            while (arr[i] > 0)
            {
                cout << ch;
                arr[i]--;
            }
        }
        cout << endl;
    }
   
    return 0;
}