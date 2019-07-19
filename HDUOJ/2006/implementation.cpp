#include <iostream>
#include <cstdio>
using namespace std;

bool isOdd(int a)
{
    return a % 2 == 1 ? true : false;
}

int main()
{
    ios::sync_with_stdio(false);
    int tmp, ans = 1, num, i = 0;
    bool isNumIndicator = true;
    while (scanf("%d", &tmp) != EOF)
    {
        if (isNumIndicator)
        {
            ans = 1;
            i = 0;
            num = tmp;
            isNumIndicator = false;
        } else {
            if (isOdd(tmp))
                ans *= tmp;
            i++;
            if (i == num)
            {
                cout << ans << endl;
                isNumIndicator = true;
            }

        }
    }
    return 0;
}
