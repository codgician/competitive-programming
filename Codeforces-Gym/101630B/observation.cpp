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

int boxArr[3], w, h;

bool cmp(int fst, int snd)
{
    if (fst > snd)
        swap(fst, snd);
    return fst <= h && snd <= w;
}

bool check()
{
    do
    {
        int a = boxArr[0], b = boxArr[1], c = boxArr[2];

        if (cmp((a + c) << 1, b + (c << 1)))
            return true;
        if (cmp(3 * b + a + c, a + c))
            return true;
        if (cmp(a + b + c, a + b + (c << 1)))
            return true;
        if (cmp(a + b + c, (b + c) << 1))
            return true;
        if (cmp(a + (b << 1) + c, a + (c << 1)))
            return true;

    } while (next_permutation(boxArr + 0, boxArr + 3));

    return false;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    for (int i = 0; i < 3; i++)
        cin >> boxArr[i];
    sort(boxArr + 0, boxArr + 3);

    cin >> w >> h;
    if (w < h)
        swap(w, h);

    cout << (check() ? "Yes" : "No") << endl;

    return 0;
}