#include <iostream>
#include <cstdio>
#include <cstdlib>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    int n;
    char str[12];
    while (scanf("%d", &n) != EOF)
    {
        itoa(n, str, 2);
        printf("%s\n", str);
    }
    return 0;
}
