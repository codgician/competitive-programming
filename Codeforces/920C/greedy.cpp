#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <string>
#include <cstring>
#include <iomanip>
#include <climits>
#include <vector>
#include <set>
#include <queue>
#include <map>
#define SIZE 200001
using namespace std;

int arr[SIZE];

int main()
{
    ios::sync_with_stdio(false);
    int eleNum;
    cin >> eleNum;
    for (int i = 0; i < eleNum; i++)
    {
        cin >> arr[i];
    }

    bool ans = true;
    int maxVal = -1;
    for (int i = 0; i < eleNum - 1; i++)
    {
        maxVal = max(maxVal, arr[i]);
        char ch;
        cin >> ch;
        if (ch == '0')
        {
            if (maxVal != i + 1)
            {
                ans = false;
                break;
            }
        }
    }

    if (ans)
        cout << "YES" << endl;
    else
        cout << "NO" << endl;

    return 0;
}
