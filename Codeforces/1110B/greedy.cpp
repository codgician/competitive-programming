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

pair<int, int> arr[SIZE];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int num, len, k;
    cin >> num >> len >> k;

    for (int i = 0; i < num; i++)
        cin >> arr[i].second;
    arr[0].first = 0;
    for (int i = 1; i < num; i++)
        arr[i].first = arr[i].second - arr[i - 1].second;

    sort(arr + 0, arr + num, [](pair<int, int> & fst, pair<int, int> & snd) {
        return fst > snd;
    });

    int ans = 1;
    for (int i = 0; i < k - 1; i++)
        ans++;
    for (int i = k - 1; i < num; i++)
        ans += arr[i].first;
    cout << ans << endl;

    return 0;
}