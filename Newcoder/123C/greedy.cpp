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

#define SIZE 100010

int arr[SIZE];

int main()
{
    ios::sync_with_stdio(false);
    int caseNum;
    cin >> caseNum;
    while (caseNum--)
    {
        int num;
        cin >> num;

        long long int ans = 0;
        int minVal = INT_MAX;
        for (int i = 0; i < num; i++)
        {
            cin >> arr[i];
            minVal = min(minVal, arr[i]);
            ans += arr[i];
        }

        ans += minVal * (num - 2);
        cout << ans << endl;
    }
    return 0;
}