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
    int len;
    cin >> len;
    for (int i = 0; i < len; i++)
    {
        long long int cnt;
        cin >> cnt;
        cout << ((cnt & 1) ? (cnt) : (cnt - 1));
        if (i < len - 1)
            cout << " ";
        else
            cout << endl;
    }
    return 0;
}