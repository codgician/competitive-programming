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
        int a, b;
        cin >> a >> b;
        a %= 100;
        b %= 100;
        cout << (a + b) % 100 << endl;
    }
    return 0;
}
