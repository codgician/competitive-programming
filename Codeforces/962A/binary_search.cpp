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
#define SIZE 200010
using namespace std;

long long int arr[SIZE];

int main()
{
    ios::sync_with_stdio(false);
    int dayNum;
    cin >> dayNum;
    arr[0] = 0;
    long long int sum = 0;
    for (int i = 1; i <= dayNum; i++)
    {
        long long int cnt;
        cin >> cnt;
        arr[i] = arr[i - 1] + cnt;
        sum += cnt;
    }

    sum = (sum + 1) >> 1;
    int dayPt = lower_bound(arr + 1, arr + dayNum + 1, sum) - arr;
    cout << dayPt << endl;
    return 0;
}
