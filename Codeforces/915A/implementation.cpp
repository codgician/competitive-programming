#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <string>
#include <iomanip>
#include <climits>
#include <vector>
#include <set>
#include <queue>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    int bucketNum, gardenLength;
    cin >> bucketNum >> gardenLength;
    int minHour = INT_MAX;
    for (int i = 0; i < bucketNum; i++)
    {
        int len;
        cin >> len;
        int cntAns;
        if (gardenLength % len == 0)
            minHour = min(minHour, gardenLength / len);
    }
    cout << minHour << endl;
    return 0;
}
