#include <iostream>
#include <cstdio>
using namespace std;

int fibb[50];

int getFibb(int a, int b, int n)
{
    return (a * fibb[n - 1] + b * fibb[n - 2]) % 7;
}

int main()
{
    ios::sync_with_stdio(false);
    fibb[1] = 1;
    fibb[2] = 1;
    int a, b, n, cycStart, cycEnd, cycLength;
    while (cin >> a >> b >> n)
    {
        if (a == 0 && b == 0 && n == 0)
            break;
        int i = 3;
        while (true)
        {
            fibb[i] = getFibb(a, b, i);
            bool flag = false;
            for (int j = 2; j < i; j++)
            {
                if (fibb[i] == fibb[j] && fibb[i - 1] == fibb[j - 1])
                {
                    flag = true;
                    cycStart = j - 1;
                    cycEnd = i - 2;
                    cycLength = i - j;
                    break;
                }
            }
            if (flag)
                break;
            i++;
        }

        if (n <= cycEnd)
            cout << fibb[n] << endl;
        else
        {
            int tmp = (n - cycStart + 1) % cycLength;
            if (tmp == 0)
                cout << fibb[cycEnd] << endl;
            else
                cout << fibb[cycStart + tmp - 1] << endl;
        }
    }
    return 0;
}
