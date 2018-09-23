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

    int caseNum;
    cin >> caseNum;
    while (caseNum--)
    {
        int len, perfectNum;
        cin >> len >> perfectNum;

        cout << perfectNum << " ";

        if (perfectNum <= (len + 1) >> 1)
        {
            if (perfectNum == 0)
                cout << 0 << endl;
            else
                cout << 1 << endl;
        }
        else
        {
            int nonPerfectNum = len - perfectNum;

            if (nonPerfectNum == 0)
                cout << perfectNum << endl;
            else
            {
                int dscPerfectNum = nonPerfectNum + 1;
                if (perfectNum % dscPerfectNum == 0)
                {
                    cout << perfectNum / dscPerfectNum << endl;
                }
                else
                {
                    cout << perfectNum / dscPerfectNum + 1 << endl;
                }
            }   
        }
    }

    return 0;
}