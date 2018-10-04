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

#define ABE_SIZE 100010
#define CD_SIZE 1010

typedef struct _Triple
{
    int a, c, d;
    int num;

    bool operator < (const struct _Triple & snd) const
    {
        if (a != snd.a)
            return a > snd.a;
        if (c != snd.c)
            return c > snd.c;
        return d > snd.d;
    }

    bool operator == (const struct _Triple & snd) const
    {
        return a == snd.a && c == snd.c && d == snd.d;   
    }

} Triple;

Triple tmpArr[ABE_SIZE], arr[ABE_SIZE];

int bArr[ABE_SIZE], bNumArr[ABE_SIZE];
int bitArr[CD_SIZE][CD_SIZE];

int getLowbit(int n)
{
    return n & -n;
}

void add(pair<int, int> pos, int val)
{
    for (int i = pos.first; i < CD_SIZE; i += getLowbit(i))
    {
        for (int j = pos.second; j < CD_SIZE; j += getLowbit(j))
        {
            bitArr[i][j] += val;
        }
    }
}

int getSum(pair<int, int> pos)
{
    int ans = 0;
    for (int i = pos.first; i > 0; i -= getLowbit(i))
    {
        for (int j = pos.second; j > 0; j -= getLowbit(j))
        {
            ans += bitArr[i][j];
        }
    }
    return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int caseNum;
    cin >> caseNum;
    for (int t = 1; t <= caseNum; t++)
    {
        memset(bitArr, 0, sizeof(bitArr));
        memset(bArr, 0, sizeof(bArr));
        memset(bNumArr, 0, sizeof(bNumArr));

        int fstNum, sndNum;
        cin >> fstNum >> sndNum;
        for (int i = 0; i < fstNum; i++)
        {
            int a, b;
            cin >> a >> b;

            if (bArr[b] == a)
            {
                bNumArr[b]++;
            }
            else if (bArr[b] < a)
            {
                bArr[b] = a;
                bNumArr[b] = 1;
            }
        }

        int tmpArrPt = 0;
        for (int i = 0; i < sndNum; i++)
        {
            int c, d, e;
            cin >> c >> d >> e;

            if (bArr[e] != 0)
            {
                tmpArr[tmpArrPt++] = {bArr[e], c, d, bNumArr[e]};
            }
        }

        sort(tmpArr + 0, tmpArr + tmpArrPt);

        int arrPt = 0;
        arr[arrPt] = tmpArr[0];
        for (int i = 1; i < tmpArrPt; i++)
        {
            if (arr[arrPt] == tmpArr[i])
                arr[arrPt].num += tmpArr[i].num;
            else
                arr[++arrPt] = tmpArr[i];
        }
        arrPt++;

        int ans = 0;
        for (int i = 0; i < arrPt; i++)
        {
            if (getSum(make_pair(1001 - arr[i].c, 1001 - arr[i].d)) == 0)
                ans += arr[i].num;
            add(make_pair(1001 - arr[i].c, 1001 - arr[i].d), 1);
        }

        cout << "Case #" << t << ": " << ans << endl;
    }

    return 0;
}