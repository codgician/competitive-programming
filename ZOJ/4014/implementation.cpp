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
#include <set>
#include <map>
#include <functional>
#include <iterator>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    int caseNum;
    cin >> caseNum;
    while (caseNum--)
    {
        int row, column, a, b;
        cin >> row >> column >> a >> b;

        int ans = 0;
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < column; j++)
            {
                int cnt;
                cin >> cnt;
                if (cnt < a || cnt > b)
                    ans++;
            }
        }

        if (a > b)
            cout << "No Solution" << endl;
        else
            cout << ans << endl;
    }
    return 0;
}
