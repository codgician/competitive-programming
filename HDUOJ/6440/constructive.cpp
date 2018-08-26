#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <string>
#include <cstring>
#include <iomanip>
#include <climits>
#include <stack>
#include <queue>
#include <vector>
#include <set>
#include <map>
#include <functional>
#include <iterator>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int caseNum;
    cin >> caseNum;
    while (caseNum--)
    {
        // define a + b (a + b) mod p
        // define a * b (a * b) mod p

        long long int p;
        cin >> p;

        for (long long int i = 0; i < p; i++)
        {
            for (long long int j = 0; j < p; j++)
            {
                cout << (i + j) % p;
                if (j < p - 1)
                    cout << " ";
                else
                    cout << endl;
            }
        }

        for (long long int i = 0; i < p; i++)
        {
            for (long long int j = 0; j < p; j++)
            {
                cout << (i * j) % p;
                if (j < p - 1)
                    cout << " ";
                else
                    cout << endl;
            }
        }
    }

    return 0;
}