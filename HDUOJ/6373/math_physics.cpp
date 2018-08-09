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

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int caseNum;
    cin >> caseNum;
    while (caseNum--)
    {
        double a, b, x, y;
        cin >> a >> b >> x >> y;
        double slopeAng = sin(atan(b / a));
        double height = y - b * (-x) / a;
        double len = (y - height) / slopeAng;

        int ans = 0;
        int cntRatio = 1, ratioSum = 0;
        while (ratioSum * 8 * height * slopeAng <= len)
        {
            ans++;
            ratioSum += cntRatio++;
        }
        cout << ans << endl;
    }
    return 0;
}