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
#include <cassert>
using namespace std;

#define SIZE 200010

int bit1[SIZE], bit2[SIZE];
int ans[SIZE], len;

int getLowbit(int n)
{
    return n & -n;
}

void add(int * bitArr, int pos, int val)
{
    for (int i = pos; i <= len; i += getLowbit(i))
        bitArr[i] += val;
}

int prefixSum(int * bitArr, int pos)
{
    int ans = 0;
    for (int i = pos; i > 0; i -= getLowbit(i))
        ans += bitArr[i];
    return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int len;
    while (cin >> len)
    {
        memset(ans, 0, sizeof(ans));
        memset(bit1, 0, sizeof(bit1));
        memset(bit2, 0, sizeof(bit2));
        string str;
        cin >> str;

        int zeroCnt = 0, oneCnt = 0, twoCnt = 0;
        for (int i = len - 1; i >= 0; i--)
        {
            bool zeroFlag = oneCnt <= 0 && twoCnt <= 0;
            oneCnt += ((str[i] == '1') << 1) - 1;
            twoCnt += ((str[i] == '2') << 1) - 1;

            if (oneCnt > 0)
            {
                ans[0] += 1;    
                ans[oneCnt] -= 1;
            }
            else if (twoCnt > 0)
            {
                ans[0] += 2;
                ans[twoCnt] -= 2;
            }
            else if ((len - i) & 1)
            {
                if (zeroFlag && str[i] == '0')
                {
                    add(bit1, oneCnt + len, 1);
                    add(bit2, twoCnt + len, 1);
                    zeroCnt++;
                }
                else
                {
                    int cnt = prefixSum(bit1, oneCnt + len - 1) + prefixSum(bit2, twoCnt + len - 1);
                    if (cnt == zeroCnt)
                    {
                        ans[0] += 1;
                        ans[1] -= 1;
                    }
                }
            }
        }
        
        while (len > 0 && ans[len] == 0)
            len--;
        for (int i = 1; i <= len; i++)
            ans[i] += ans[i - 1];
        for (int i = 0, cf = 0; i <= len; i++)
        {
            ans[i] += cf;
            cf = ans[i] / 10;
            ans[i] %= 10;
            if (cf > 0 && i == len)
                len++;
        }
        while (len > 0 && ans[len] == 0)
            len--;
        for (int i = len; i >= 0; i--)
            cout << ans[i];
        cout << endl;
    }

    return 0;
}