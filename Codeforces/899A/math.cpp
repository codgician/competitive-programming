#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <string>
#include <iomanip>
#include <climits>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    int groupNum;
    cin >> groupNum;
    int oneNum = 0, twoNum = 0;
    for (int i = 0; i < groupNum; i++)
    {
        int cnt;
        cin >> cnt;
        if (cnt == 1)
            oneNum++;
        else if (cnt == 2)
            twoNum++;
    }

    int ans;
    if (twoNum >= oneNum)
    {
        ans = oneNum;
    }
    else
    {
        ans = twoNum + (oneNum - twoNum) / 3;
    }
    cout << ans << endl;
    return 0;
}
