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

#define SIZE 200010

pair<long long int, long long int> arr[SIZE];
long long int dsc[SIZE << 1], ans[SIZE];
long long int prefixSum[SIZE << 1];

int main()
{
    ios::sync_with_stdio(false);
    int num;
    cin >> num;
    for (int i = 0; i < num; i++)
    {
        cin >> arr[i].first >> arr[i].second;
        dsc[i << 1] = arr[i].first;
        dsc[i << 1 ^ 1] = arr[i].second + 1;
    }

    sort(dsc + 0, dsc + (num << 1));
    int dscLen = unique(dsc + 0, dsc + (num << 1)) - dsc;

    for (int i = 0; i < num; i++)
    {
        int leftPt = lower_bound(dsc + 0, dsc + dscLen, arr[i].first) - dsc;
        int rightPt = lower_bound(dsc + 0, dsc + dscLen, arr[i].second + 1) - dsc;
        prefixSum[leftPt]++;
        prefixSum[rightPt]--;
    } 
    for (int i = 1; i < (num << 1); i++)
    {
        prefixSum[i] += prefixSum[i - 1];
    }

    memset(ans, 0, sizeof(ans));
    for (int i = 0; i < (num << 1); i++)
    {
        ans[prefixSum[i]] += dsc[i + 1] - dsc[i];
    }

    for (int i = 1; i <= num; i++)
    {
        cout << ans[i];
        if (i < num)
            cout << " ";
        else
            cout << endl;
    }

    return 0;
}