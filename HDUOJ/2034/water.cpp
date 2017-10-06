#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

int n, m, a[10010], b[10010], ans[10010];

bool checkExist(int x)
{
    for (int i = 0; i < m; i++)
    {
        if (x == b[i])
            return true;
    }
    return false;
}

int main()
{
    ios::sync_with_stdio(false);
    while (cin >> n >> m)
    {
        int pt = 0;

        if (n == 0 && m == 0)
            break;

        for (int i = 0; i < n; i++)
            cin >> a[i];
        for (int i = 0; i < m; i++)
            cin >> b[i];

        for (int i = 0; i < n; i++)
            if (!checkExist(a[i]))
            {
                ans[pt] = a[i];
                pt++;
            }

        if (pt == 0)
            cout << "NULL";
        else
        {
            sort(ans, ans + pt);
            for (int i = 0; i < pt; i++)
            {
                cout << ans[i] << " ";
            }
        }
        cout << endl;
    }
    return 0;
}
