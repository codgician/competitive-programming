#include <iostream>
#include <cstdio>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    int caseNum;
    cin >> caseNum;
    for (int t = 0; t < caseNum; t++)
    {
        double a, b, c;
        cin >> a >> b >> c;
        if (a > c)
            swap(a, c);
        if (b > c)
            swap(b, c);
        if (a > b)
            swap(a, b);
        if (a + b > c || c - b < a)
            cout << "YES" << endl;
        else
            cout << "NO" << endl;
    }
    return 0;
}
