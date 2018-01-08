#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <string>
#include <iomanip>
#include <climits>
#include <set>
#include <vector>
#include <queue>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    long long int n, m;
    cin >> n >> m;

    if (n >= 32)
    {
        cout << m << endl;
    }
    else
    {
        long long int tmp = ((long long int)1 << n);
        cout << m % tmp << endl;
    }
    return 0;
}
