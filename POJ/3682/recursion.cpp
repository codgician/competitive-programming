#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <string>
#include <cstring>
#include <iomanip>
#include <climits>
#include <vector>
#include <set>
#include <queue>
#include <map>
#define SIZE 1001
using namespace std;

double exDay[SIZE], exCost[SIZE];

int main()
{
    ios::sync_with_stdio(false);
    int headTimes;
    while (cin >> headTimes)
    {
        if (headTimes == 0)
            break;

        double headProb;
        cin >> headProb;

        exDay[0] = 0;
        exCost[0] = 0;
        for (int i = 1; i <= headTimes; i++)
        {
            exDay[i] = i / headProb;
            exCost[i] = exCost[i - 1] + exDay[i - 1] * 2 + 1 + (1 - headProb) * (exDay[i] * 2 + 1) / headProb;
        }
        cout << fixed << setprecision(3) << exDay[headTimes] << " " << exCost[headTimes] << endl;
    }
    return 0;
}
