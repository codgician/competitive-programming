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

#define SIZE 81

// n! * m! * A(nm, nm - (n + m - 1))

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int caseNum;
    cin >> caseNum;
    while (caseNum--)
    {
        int row, column, mod;
        cin >> row >> column >> mod;
        
        long long int ans = 1;
        for (int i = 1; i <= row; i++)
        {
            ans *= i;
            if (ans >= mod)
                ans %= mod;
        }

        for (int i = 1; i <= column; i++)
        {
            ans *= i;
            if (ans >= mod)
                ans %= mod;
        }

        for (int i = row * column; i >= row + column; i--)
        {
            ans *= i;
            if (ans >= mod)
                ans %= mod;
        }

        cout << ans << endl;
    }
    return 0;
}