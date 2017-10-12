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
    fibb[0] = 1;
    fibb[1] = 1;
    int a, b, n;
    while (cin >> a >> b >> n)
    {
        if (a == 0 && b == 0 && n == 0)
            break;
        int cntPt;
        for (cntPt = 2; cntPt < 50; cntPt++)
        {
            fibb[cntPt] = getFibb(a, b, cntPt);
            if (fibb[cntPt] == fibb[1] && fibb[cntPt - 1] == fibb[0])
                break;
        }
        int tmp = n % (cntPt - 1);
        if (tmp == 0)
            cout << fibb[cntPt - 2] << endl;
        else
            cout << fibb[tmp - 1] << endl;
    }
    return 0;
}
