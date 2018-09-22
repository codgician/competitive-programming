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
    cin.tie(0);
    cout.tie(0);

    int num;
    cin >> num;
    if ((num - 2) % 3 != 0)
    {
        cout << "1 1 " << num - 2 << endl;
    }
    else if ((num - 3) % 3 != 0)
    {
        cout << "1 2 " << num - 3 << endl;
    }
    else
    {
        cout << "2 2 " << num - 4 << endl;
    }

    return 0;
}