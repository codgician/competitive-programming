#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <string>
#include <iomanip>
#include <climits>
using namespace std;

int v[10] = {4, 2, 2, 2, 3, 2, 3, 2, 4, 3};
int h[10] = {2, 0, 3, 3, 1, 3, 3, 1, 3, 3};

int main()
{
    ios::sync_with_stdio(false);
    int caseNum;
    cin >> caseNum;
    while (caseNum--)
    {
        string str;
        cin >> str;
        int hans = 0, vans = 0;
        for (int i = 0; i < str.length(); i++)
        {
            hans += h[str[i] - '0'];
            vans += v[str[i] - '0'];
        }
        cout << hans << " " << vans << endl;
    }
    return 0;
}
