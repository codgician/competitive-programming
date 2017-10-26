#include <iostream>
#include <cstdio>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    long long int a, b;
    while (scanf("%llX%llX", &a, &b) != EOF)
    {
        long long int ans = a + b;
        if (ans < 0)
            printf("-%llX\n", -ans);
        else
            printf("%llX\n", a + b);
    }
    return 0;
}
