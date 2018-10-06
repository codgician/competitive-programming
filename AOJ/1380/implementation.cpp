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
    cin.tie(0);
    cout.tie(0);

    int num, t;
    while (cin >> num >> t)
    {
        for (int i = 0; i < num; i++)
        {
            cin >> arr[i];
        }

        long long int pfxSum = 0;
        int maxNum = -1;
        for (int i = 0; i < num; i++)
        {
            pfxSum += arr[i];
            maxNum = max(maxNum, arr[i]);

            if (t < pfxSum)
                cout << 1 << endl;
            else
                cout << (t - pfxSum) / maxNum + 2 << endl;
        }
    }

    return 0;
}