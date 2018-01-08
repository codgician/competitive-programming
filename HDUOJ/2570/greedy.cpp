#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <string>
#include <climits>
#include <iomanip>
#define SIZE 101
using namespace std;

int arr[SIZE];

int main()
{
    ios::sync_with_stdio(false);
    int caseNum;
    cin >> caseNum;
    while (caseNum--)
    {
        int n, v;
        double p;
        cin >> n >> v >> p;
        for (int i = 0; i < n; i++)
        {
            cin >> arr[i];
        }
        sort(arr + 0, arr + n);
        int prefixSum = 0, cnt = 0;
        double ans = 0;
        for (int i = 0; i < n; i++)
        {
            prefixSum += arr[i];
            if ((double)prefixSum / (cnt + 1) > p)
                break;
            cnt++;
            ans = (double)prefixSum / cnt;
        }
        cout << cnt * v << " " << fixed << setprecision(2) << ans / 100 << endl;
    }
    return 0;
}
