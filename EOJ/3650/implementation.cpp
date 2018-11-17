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

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    string fst, snd;
    cin >> fst >> snd;

    if (fst > snd)
        swap(fst, snd);

    fst[snd.size() - 1] += 1;
    for (int i = fst.size() - 1; i >= 0; i--)
    {
        if (fst[i] > 'Z')
        {
            fst[i] = 'A';
            if (i >= 1)
                fst[i - 1] += 1;
        }
    }

    cout << fst << endl;

    return 0;
}