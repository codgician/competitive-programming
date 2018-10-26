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

#define SIZE 200010

bool isInStack[SIZE];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    memset(isInStack, false, sizeof(isInStack));
    queue<int> stk;
    int num;
    cin >> num;

    for (int i = 0; i < num; i++)
    {
        int cnt;
        cin >> cnt;
        isInStack[cnt] = true;
        stk.push(cnt);
    }

    for (int i = 0; i < num; i++)
    {
        int cnt;
        cin >> cnt;

        if (!isInStack[cnt])
        {
            cout << 0 << " ";
            continue;
        }

        int ans = 0;
        while (!stk.empty())
        {
            int cntTop = stk.front();
            stk.pop();
            isInStack[cntTop] = false;
            ans++;

            if (cntTop == cnt)
                break;
        }
        cout << ans << " ";
    }
    cout << endl;

    return 0;
}