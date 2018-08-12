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
        int row, column, num;
        cin >> row >> column >> num;

        long long int ans = 0;
        for (int i = 0; i < num; i++)
        {
            int x, y;
            cin >> x >> y;
            ans += min(min(row - x, x), min(column - y, y));
        }
        cout << ans << endl;
    }
    return 0;
}