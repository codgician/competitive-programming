#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
using namespace std;

int getGirlFriend(int n)
{
    int ans = 1;
    for (int i = 2; i <= sqrt(n); i++)
    {
        if (n % i == 0)
        {
            ans += i;
            if (i != sqrt(n))
                ans += n / i;
        }
    }
    return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    int caseNum;
    cin >> caseNum;
    for (int t = 0; t < caseNum; t++)
    {
        int n;
        cin >> n;
        cout << getGirlFriend(n) << endl;
    }
    return 0;
}
