#include <iostream>
#include <cstdio>
#include <string>
#include <cstring>
#include <cmath>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    int caseNum;
    cin >> caseNum;
    for (int t = 0; t < caseNum; t++)
    {
        int n;
        int water[4];
        cin >> n;
        water[0] = n % 10;
        for (int i = 1; i < 4; i++)
            water[i] = (water[i - 1] * (n % 10)) % 10;
        if (n % 4 == 0)
            cout << water[3] << endl;
        else
            cout << water[n % 4 - 1] << endl;
    }
    return 0;
}
