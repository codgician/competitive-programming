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
#include <bitset>
#include <functional>
#include <iterator>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int coinNum, lowerBound, upperBound;
    while (cin >> coinNum >> lowerBound >> upperBound)
    {
        if (coinNum % (lowerBound + upperBound) == 0)
        {
            cout << "WIN" << endl;
        }
        else
        {
            if (coinNum % (lowerBound + upperBound) <= lowerBound)
            {
                cout << "LOST" << endl;
            }
            else
            {
                cout << "WIN" << endl;
            }
        }
    }
    return 0;
}