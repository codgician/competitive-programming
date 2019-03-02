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

#define SIZE 200010

long long int arr[SIZE];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int len;
    long long int num, lim;
    cin >> len >> num >> lim;
    for (int i = 0; i < len; i++)
        cin >> arr[i];
    arr[len++] = 0;
    sort(arr + 0, arr + len, greater<long long int>());

    long long int cycl = arr[0] * lim + arr[1];
    long long int ans = 1ll * (num / (lim + 1)) * cycl + (num % (lim + 1)) * arr[0];
    cout << ans << endl;

    return 0;
}