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

long long int a, b, c, d, v, t;

long long int work(long long int timer, long long int t)
{
    long long int aPt = 0, bPt = 0, prevPt = 0;
    long long int counter = 0;

    bool light = false;
    if (timer > 0)
    {
        light = true;
        // Skip first round
        aPt += a;
        bPt += c;
    }

    while (min(aPt, bPt) <= t)
    {
        long long int cntPt = min(aPt, bPt);

        if (light)
        {
            timer -= (cntPt - prevPt) << 1;
            if (timer <= 0)
            {
                timer = 0;
                light = false;
            }
        }

        if (cntPt == bPt)
        {
            bPt += c;

            if (!light)
            {
                light = true;
                timer = (v << 1) + 1;
                counter += d - 1;
            }
            else
            {
                timer = (v << 1) + 1;
                counter += d;
            }
        }

        if (cntPt == aPt)
        {
            aPt += a;
            // click b times

            if (!light)
            {
                light = true;
                timer = (v << 1) + 1;
                counter += b - 1;
            }
            else
            {
                timer = (v << 1) + 1;
                counter += b;
            }
        }

        prevPt = cntPt;
    }

    return counter;
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
        cin >> a >> b >> c >> d >> v >> t;

        long long int lcm = a * c / __gcd(a, c);
        if (t <= lcm)
        {
            cout << work(0, t) << endl;
        }
        else
        {
            long long int ans = 0;

            // First round
            ans += work(0, 0);
            // Remaining cycles
            ans += t / lcm * work((v << 1) + 1, lcm);
            // Last non-cycle
            if (t % lcm > 0)
                ans += work((v << 1) + 1, t % lcm);

            cout << ans << endl;
        }
    }

    return 0;
}