// Cycle: 1, 2, 0, 2, 2, 1, 0, 1, 1, 2, ...
#include <iostream>
#include <cstdio>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    int n;
    while (cin >> n)
    {
        if (n % 8 == 2 || n % 8 == 6)
            cout << "yes" << endl;
        else
            cout << "no" << endl;
    }
    return 0;
}
