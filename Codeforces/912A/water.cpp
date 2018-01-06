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
    long long int yellowNum, blueNum;
    cin >> yellowNum >> blueNum;
    long long int yellowReq, greenReq, blueReq;
    cin >> yellowReq >> greenReq >> blueReq;
    long long int yellowNeed = 0, blueNeed = 0;
    yellowNeed = yellowReq * 2 + greenReq;
    blueNeed = greenReq + blueReq * 3;

    long long int ans = 0;
    if (yellowNeed > yellowNum)
    {
        ans += (yellowNeed - yellowNum);
    }
    if (blueNeed > blueNum)
    {
        ans += (blueNeed - blueNum);
    }
    cout << ans << endl;
    return 0;
}
