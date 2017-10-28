#include <iostream>
#include <cstdio>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    int n;
    while (cin >> n)
    {
        int num = 1;
        for (int i = 2; i <= n; i++)
        {
            int tmp = 1;
            while (n % i == 0)
            {
                n /= i;
                tmp++;
            }
            num *= tmp;
        }
        if (num & 1)
            cout << 1 << endl;
        else
            cout << 0 << endl;
    }
    return 0;
}
