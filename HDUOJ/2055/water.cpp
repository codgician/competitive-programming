#include <iostream>
#include <cstdio>
#include <string>
#include <cstring>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    int caseNum;
    cin >> caseNum;
    for (int t = 0; t < caseNum; t++)
    {
        char ch;
        int x, y;
        cin >> ch >> y;
        if (ch >= 'A' && ch <= 'Z')
        {
            x = ch - 'A' + 1;
        }
        else if (ch >= 'a' && ch <= 'z')
        {
            x = -(ch - 'a' + 1);
        }
        cout << x + y << endl;
    }
    return 0;
}
