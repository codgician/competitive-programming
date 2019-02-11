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

    int arr[3];
    while (cin >> arr[0] >> arr[1] >> arr[2])
    {
        if ((arr[0] & 1) && (arr[1] & 1) && (arr[2] & 1))
            cout << "No" << endl;
        else
            cout << "Yes" << endl;
    }

    return 0;
}