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
#include <bitset>
#include <cassert>
using namespace std;

#define SIZE 100010

int arr[SIZE], len, num;
long long int a, b;

long long int dfs(int leftPt, int rightPt)
{
    int leftPos = lower_bound(arr + 0, arr + num, leftPt) - arr;
    if (leftPos >= num || arr[leftPos] > rightPt)
        return a;

    int rightPos = upper_bound(arr + 0, arr + num, rightPt) - arr;
    while (rightPos >= num || arr[rightPos] > rightPt)
        rightPos--;
    int num = rightPos - leftPos + 1, midPt = (leftPt + rightPt) >> 1;

    if (leftPt == rightPt)
        return b * num;
    return min(b * num * (rightPt - leftPt + 1), dfs(leftPt, midPt) + dfs(midPt + 1, rightPt));
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> len >> num >> a >> b;
    for (int i = 0; i < num; i++)
    {
        cin >> arr[i];
        arr[i]--;
    }
    sort(arr + 0, arr + num);
    len = 1 << len;

    cout << dfs(0, len - 1) << endl;
    return 0;
}