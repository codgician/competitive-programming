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

#define SIZE 1010

int arr[SIZE];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int num;
    cin >> num;
    for (int i = 0; i < num; i++)
    {
        cin >> arr[i];
    }

    int ans = INT_MAX, ansLen = INT_MAX;
    for (int i = 1; i <= 100; i++)
    {
        int cntAns = 0;
        for (int j = 0; j < num; j++)
        {
            if (arr[j] > i + 1)
                cntAns += arr[j] - i - 1;
            else if (arr[j] < i - 1)
                cntAns += i - 1 - arr[j];
        }
       
        if (cntAns < ans)
        {
            ans = cntAns;
            ansLen = i;
        }
    }

    cout << ansLen << " " << ans << endl;
    return 0;
}