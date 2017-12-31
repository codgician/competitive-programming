#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <string>
#include <iomanip>
#include <climits>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    int caseNum;
    cin >> caseNum;
    while (caseNum--)
    {
        int n;
        cin >> n;
        int mod = n % 7;
        int stdAns = (n / 7) * 2;
        if (mod == 0)
        {
            cout << stdAns << " " << stdAns << endl;
        }
        else if (mod == 1)
        {
            cout << stdAns << " " << stdAns + 1 << endl;
        }
        else if (mod == 6)
        {
            cout << stdAns + 1 << " " << stdAns + 2 << endl;
        }
        else
        {
            cout << stdAns << " " << stdAns + 2 << endl;
        }
    }
    return 0;
}
