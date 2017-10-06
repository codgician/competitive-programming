#include <iostream>
#include <cstdio>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    int a, b;
    while (cin >> a >> b)
    {
        if (a == 0 && b == 0)
            break;
        cout << a + b << endl;
    }
    return 0;
}
