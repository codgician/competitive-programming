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
    long long int len, qNum;
    cin >> len >> qNum;
    while (qNum--)
    {
        long long int pos;
        cin >> pos;

        if (pos & 1)
        {
            cout << ((pos + 1) >> 1) << endl;
        }
        else
        {
            long long int cntLayer = len;
            while (!(pos & 1))
            {
                cntLayer -= pos >> 1;
                pos = cntLayer;
            }
            cout << ((pos + 1) >> 1) + (len - cntLayer) << endl;
        }
    }
    return 0;
}