#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <string>
#include <climits>
#include <iomanip>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    int caseNum;
    cin >> caseNum;
    while (caseNum--)
    {
        string a, b;
        cin >> a >> b;
        for (int i = 0; i < a.length() / 2; i++)
        {
            cout << a[i];
        }
        cout << b;
        for (int i = a.length() / 2; i < a.length(); i++)
        {
            cout << a[i];
        }
        cout << endl;
    }
    return 0;
}
