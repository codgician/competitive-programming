#include <iostream>
#include <cstdio>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    long long int a, b;
    while (cin >> a >> b)
    {
        cout << a * b - a - b << " " << (a - 1) * (b - 1) / 2 << endl;
    }
    return 0;
}
