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
    
    int qNum;
    cin >> qNum;
    while (qNum--)
    {
        long long int x, y, step;
        cin >> x >> y >> step;

        long long int minStep = max(x, y);
        long long int ans = step;

        if (step < minStep)
        {
            cout << -1 << endl;
            continue;
        }
        
        if (abs(x - y) & 1)
        {
            ans -= 1;
        }
        else if (abs(step - min(x, y)) & 1)
        {
            ans -= 2;
        }

        cout << ans << endl;
    }

    return 0;
}