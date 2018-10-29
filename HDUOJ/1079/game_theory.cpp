#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <string>
#include <string>
#include <climits>
#include <iomanip>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    int caseNum;
    cin >> caseNum;
    while (caseNum--)
    {
        int year, month, day;
        cin >> year >> month >> day;
        if (((month + day) & 1) == 0 || (month == 9 && day == 30) || (month == 11 && day == 30))
            cout << "YES" << endl;
        else
            cout << "NO" << endl;
    }
    return 0;
}
