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

#define SIZE 100100

int arr[SIZE];

int main()
{
    ios::sync_with_stdio(false);
    int len;
    cin >> len;
    for (int i = 0; i < len; i++)
    {
        cin >> arr[i];
    }
    sort(arr + 0, arr + len);

    int cntPt = 0, ans = 0;
    for (int i = 0; i < len; i++)
    {
        while (cntPt < len && arr[cntPt] <= arr[i])
            cntPt++;
        if (cntPt >= len)
            break;
        ans++;
        cntPt++;
    }

    cout << ans << endl;
    return 0;
}