// Orz orz orz!
// This is a math problem!

// n = a^3 - b^3 = (a - b)(a^2 + ab + b^2)
// Since n is a prime number, a - b = 1 => a = b + 1
// Therefore n = (b + 1)^2 + ab + b^2 = 3b(b + 1) + 1

#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    int caseNum;
    cin >> caseNum;
    for (int t = 0; t < caseNum; t++)
    {
        long long int n;
        cin >> n;
        if ((n - 1) % 3 != 0)
            cout << "NO";
        else
        {
            n = (n - 1) / 3;
            long long int tmp = sqrt(n);
            if (tmp * (tmp + 1) == n)
                cout << "YES";
            else
                cout << "NO";
        }
        cout << endl;
    }
    return 0;
}
