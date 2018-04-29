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
#include <stack>
#include <functional>
#include <iterator>
#define SIZE 100010
#define OFFSET 200010
#define BUCKET_SIZE 400040
using namespace std;

int arr[SIZE], bucket[BUCKET_SIZE];

int main()
{
    ios::sync_with_stdio(false);
    int caseNum;
    cin >> caseNum;
    while (caseNum--)
    {
        memset(bucket, 0, sizeof(bucket));
        int len;
        cin >> len;
        for (int i = 0; i < len; i++)
            cin >> arr[i];

        int minDelta = INT_MAX, maxDelta = INT_MIN;
        for (int i = 0; i < len; i++)
        {
            int cnt;
            cin >> cnt;
            int delta = cnt - arr[i] + OFFSET;
            bucket[delta]++;
            minDelta = min(minDelta, delta);
            maxDelta = max(maxDelta, delta);
        }

        int maxVal = -1;
        for (int i = minDelta; i <= maxDelta; i++)
        {
            maxVal = max(maxVal, bucket[i]);
        }

        cout << maxVal << endl;
    }
    return 0;
}