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

#define SIZE 100010

int arr[2][SIZE], len;

bool check()
{
    if (arr[0][0] != arr[1][0] || arr[0][len - 1] != arr[1][len - 1])
        return false;
    for (int t = 0; t < 2; t++)
    {
        for (int i = 0; i < len - 1; i++)
            arr[t][i] = abs(arr[t][i + 1] - arr[t][i]);
        sort(arr[t] + 0, arr[t] + len - 1);
    }

    for (int i = 0; i < len - 1; i++)
        if (arr[0][i] != arr[1][i])
            return false;
    return true;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> len; 
    for (int t = 0; t < 2; t++)
        for (int i = 0; i < len; i++)
            cin >> arr[t][i];
        
    if (check())
        cout << "Yes" << endl;
    else
        cout << "No" << endl;

    return 0;
}