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

const double pi = acos(-1.0);
const double eps = 1e-6;

typedef struct _Circle
{
    int x, y;
    int r;

    _Circle(int px, int py, int pr)
    {
        x = px;
        y = py;
        r = pr;
    }
} Circle;

double getDistance(Circle & fst, Circle & snd)
{
    return sqrt((fst.x - snd.x) * (fst.x - snd.x) + (fst.y - snd.y) * (fst.y - snd.y));
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int caseNum;
    cin >> caseNum;
    while (caseNum--)
    {
        int num, R;
        cin >> num >> R;

        Circle bgCircle(0, 0, R);
        double ans = 2 * pi * R;
        for (int i = 0; i < num; i++)
        {
            int x, y, r;
            cin >> x >> y >> r;

            Circle cntCircle(x, y, r);
            double dis = getDistance(bgCircle, cntCircle);

            if (dis - (R + r) > 0 || dis - (R - r) < 0)
                continue;
            if (dis - (R - r) == 0)
            {
                ans += 2 * pi * r;
                continue;
            }

            double ang1 = (R * R + dis * dis - r * r) / (2 * R * dis);
            double ang2 = (r * r + dis * dis - R * R) / (2 * r * dis);
            ans -= R * 2 * acos(ang1);
            ans += r * 2 * acos(ang2);
        }

        cout << fixed << setprecision(7) << ans << endl;
    }
    return 0;
}