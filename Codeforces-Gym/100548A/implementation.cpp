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
    for (int t = 1; t <= caseNum; t++)
    {
        int num;
        cin >> num;

        bool ans = true;
        for (int i = 0; i < num; i++)
        {
            long long int cnt;
            cin >> cnt;
            if (ans && cnt % 3 != 0)
            {
                ans = false;
            }
        }

        cout << "Case #" << t << ": ";
        if (ans)
            cout << "Yes" << endl;
        else
            cout << "No" << endl;
    }

    return 0;
}