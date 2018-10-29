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
    int cardNum;
    while (cin >> cardNum)
    {
        if (cardNum % 3 == 0)
            cout << "Cici" << endl;
        else
            cout << "Kiki" << endl;
    }
    return 0;
}
