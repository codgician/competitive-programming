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
        int stopCond, onceMax;
        cin >> stopCond >> onceMax;
        if (stopCond % (onceMax + 1) == 0)
            cout << "Rabbit" << endl;
        else
            cout << "Grass" << endl;
    }
    return 0;
}
