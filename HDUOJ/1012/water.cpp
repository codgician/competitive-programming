#include <iostream>
#include <cstdio>
#include <cmath>
#include <iomanip>
using namespace std;

int getFactorial(int a)
{
    if (a == 0)
        return 1;
    int ans = 1;
    for (int i = a; i > 1; i--)
        ans *= i;
    return ans;
}

double f(int i)
{
    double ans = 0;
    for (int t = 0; t <= i; t++)
        ans += (double)1 / getFactorial(t);
    return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    cout << "n e" << endl << "- -----------" << endl;
    printf("0 1\n1 2\n2 2.5\n");
    for (int i = 3; i < 10; i++)
        printf("%d %.9lf\n", i, f(i));
    return 0;
}
