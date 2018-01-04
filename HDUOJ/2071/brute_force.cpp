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
        int stuNum;
        cin >> stuNum;
        double maxHeight = -1;
        while (stuNum--)
        {
            double cntHeight;
            cin >> cntHeight;
            maxHeight = max(maxHeight, cntHeight);
        }
        cout << fixed << setprecision(2) << maxHeight << endl;
    }
    return 0;
}
