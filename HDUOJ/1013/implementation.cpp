#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
using namespace std;

int getLength(int n)
{
    int ans = 0;
    while (n > 0)
    {
        n /= 10;
        ans++;
    }
    return ans;
}

int getPower(int a, int n)
{
    if (n == 0)
        return 1;
    int ans = a;
    for (int i = 1; i < n; i++)
    {
        ans *= a;
    }
    return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    string str;
    while (cin >> str)
    {
        if (str == "0")
            break;
        int ans = 0, tmp;
        for (int i = 0; i < str.length(); i++)
            ans += str[i] - '0';
        while (ans > 9)
        {
            tmp = ans;
            ans = 0;
            for (int i = 0; i < getLength(tmp); i++)
                ans += (tmp / getPower(10, i)) % 10;
        }
        cout << ans << endl;
    }
    return 0;
}
