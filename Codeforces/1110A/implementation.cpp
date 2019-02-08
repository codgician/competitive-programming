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

#define SIZE 100010

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int len, base;
    cin >> base >> len;

    int ans = 0;
    for (int i = 0; i < len; i++)
    {
        int cnt;
        cin >> cnt;
        cnt &= 1;
        ans = (ans * base) + cnt;
        ans &= 1; 
    }

    if (ans & 1)
        cout << "odd" << endl;
    else
        cout << "even" << endl;

    return 0;
}