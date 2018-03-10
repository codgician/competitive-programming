#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <string>
#include <iomanip>
#include <climits>
#include <vector>
#include <queue>
#include <set>
#include <map>
#define SIZE 100010
using namespace std;

long long int arr[SIZE];

int main()
{
    ios::sync_with_stdio(false);
    int caseNum;
    cin >> caseNum;
    while (caseNum--)
    {
        int n, m;
        cin >> n >> m;
        for (int i = 0; i < n; i++)
        {
            cin >> arr[i];
        }
        sort(arr + 0, arr + n);

        long long int ans = 0;
        m <<= 1;
        for (int i = 0; i < (m >> 1); i++)
        {
            ans += arr[i] * arr[m - i - 1];
        }
        cout << ans << endl;
    }
    return 0;
}
