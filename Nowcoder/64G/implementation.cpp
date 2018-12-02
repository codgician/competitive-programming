#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <string>
#include <iomanip>
#include <climits>
using namespace std;

int getType(string s)
{
    if (s == "Jin")
        return 0;
    else if (s == "Mu")
        return 1;
    else if (s == "Tu")
        return 2;
    else if (s == "Shui")
        return 3;
    else if (s == "Huo")
        return 4;
    return 0;
}

int main()
{
    ios::sync_with_stdio(false);
    int round;
    cin >> round;
    int aliceScr = 0, bobScr = 0;
    while (round--)
    {
        string s1, s2;
        cin >> s1 >> s2;
        int a, b;
        a = getType(s1);
        b = getType(s2);
        if (a + 1 == b || (a == 4 && b == 0))
            aliceScr++;
        else if (b + 1 == a || (b == 4 && a == 0))
            bobScr++;
    }
    if (aliceScr > bobScr)
        cout << "Alice" << endl;
    else if (aliceScr < bobScr)
        cout << "Bob" << endl;
    else
        cout << "Draw" << endl;
    return 0;
}
