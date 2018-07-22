#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <string>
#include <iomanip>
#include <climits>
#include <vector>
#include <queue>
#include <set>
#include <map>
using namespace std;

#define SIZE 200010

int arr[SIZE];
int bitArr[SIZE];

int num;

inline int getLowbit(int n)
{
    return n & -n;
}

inline void update(int pos, int val)
{
    arr[pos] = val;
    for (int i = pos; i <= num; i += getLowbit(i))
    {
        bitArr[i] = val;
        for (int j = 1; j < getLowbit(i); j <<= 1)
        {
            bitArr[i] = max(bitArr[i], bitArr[i - j]);
        }
    }
}

inline int query(int leftPt, int rightPt)
{
    int ans = INT_MIN;
    while (rightPt >= leftPt)
    {
        ans = max(ans, arr[rightPt]);
        rightPt--;
        while (rightPt - getLowbit(rightPt) >= leftPt)
        {
            ans = max(ans, bitArr[rightPt]);
            rightPt -= getLowbit(rightPt);
        }
    }

    return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    int oprNum;
    while (cin >> num >> oprNum)
    {
        memset(bitArr, 0, sizeof(bitArr));
        for (int i = 1; i <= num; i++)
        {
            int cnt;
            cin >> cnt;
            update(i, cnt);
        }

        while (oprNum--)
        {
            char opr;
            cin >> opr;
            if (opr == 'Q')
            {
                int leftPt, rightPt;
                cin >> leftPt >> rightPt;
                if (leftPt > rightPt)
                    swap(leftPt, rightPt);

                int ans = query(leftPt, rightPt);
                cout << ans << endl;
            }
            else if (opr == 'U')
            {
                int pos, val;
                cin >> pos >> val;
                update(pos, val);
            }
        }
    }
    return 0;
}
