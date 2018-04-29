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
#include <map>
#include <set>
#include <stack>
#include <functional>
#include <iterator>
#define SIZE 100010
using namespace std;

long long int arr[SIZE];
long long int n, m;

long long int getId(char ch, int rank)
{
    if (ch == 'W')
        return 0;

    int type = 0;
    if (ch == 'C')
        type = 0;
    else if (ch == 'B')
        type = 1;
    else if (ch == 'D')
        type = 2;

    long long int ans = m * type + rank;

    return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    int caseNum;
    cin >> caseNum;
    while (caseNum--)
    {
        cin >> n >> m;
        
        int wPos = -1;
        for (int i = 0; i < n; i++)
        {
            char ch;
            cin >> ch;
            if (ch == 'W')
            {
                wPos = i;
                arr[i] = 0;
            }
            else
            {
                long long int rank;
                cin >> rank;
                arr[i] = getId(ch, rank);
            }
        }

        long long int ans = -1;
        if (n == 1)
        {
            cout << 3 * m << endl;
            continue;
        }

        if (n > 1 && arr[1] != 0 && arr[0] > arr[1])
        {
            cout << 1 << endl;
            continue;
        }

        if (wPos == -1)
        {
            ans = 3 * m - n + 1;
        }
        else if (wPos == 0)
        {
            ans = arr[1] - 1;
        }
        else if (wPos == n - 1)
        {
            ans = 3 * m - arr[wPos - 1];
            if (wPos == 1)
            {
                ans++;
            }
        }
        else
        {
            ans = arr[wPos + 1] - arr[wPos - 1] - 1;
            if (wPos == 1)
            {
                ans++;
            }
        }

        cout << ans << endl;
    }
    return 0;
}