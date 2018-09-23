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

    bool ans = false;
    for (int i = 0; i < num; i++)
    {
        int cnt;
        cin >> cnt;
        if (cnt == 1)
            ans = true;
    }

    if (ans)
        cout << "HARD" << endl;
    else
        cout << "EASY" << endl;

    return 0;
}