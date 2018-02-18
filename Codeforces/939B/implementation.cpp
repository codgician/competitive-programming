#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <string>
#include <cstring>
#include <iomanip>
#include <climits>
#include <vector>
#include <set>
#include <queue>
#include <map>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    long long int hamsterNum;
    int boxType;
    cin >> hamsterNum >> boxType;

    int minBoxPt;
    long long int minMod = 1e18 + 1, cntAns;
    for (int i = 0; i < boxType; i++)
    {
        long long int boxSize;
        cin >> boxSize;
        long long int cntMod = hamsterNum % boxSize;
        if (cntMod < minMod)
        {
            minMod = cntMod;
            minBoxPt = i + 1;
            cntAns = hamsterNum / boxSize;
        }
    }
    cout << minBoxPt << " " << cntAns << endl;
    return 0;
}
