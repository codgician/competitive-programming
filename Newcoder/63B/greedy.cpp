#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <string>
#include <iomanip>
#include <climits>
#define SIZE 1001
using namespace std;

int arr[SIZE];

bool cmpRule(int a, int b)
{
    return a > b;
}

int main()
{
    ios::sync_with_stdio(false);
    int caseNum;
    cin >> caseNum;
    while (caseNum--)
    {
        int nationNum;
        cin >> nationNum;
        for (int i = 0; i < nationNum; i++)
        {
            cin >> arr[i];
        }
        sort(arr + 0, arr + nationNum, cmpRule);
        int ans = 0;
        for (int i = 0; i < nationNum; i++)
        {
            if (arr[i] < i + 1)
            {
                if (i > 0)
                    ans = i;
                break;
            }
        }
        if (ans == 1)
            ans = 0;
        cout << ans << endl;
    }
    return 0;
}
