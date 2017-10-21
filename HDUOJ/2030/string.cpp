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
    getchar();

    for (int t = 0; t < caseNum; t++)
    {
        string str;
        int ans = 0;
        getline(cin, str);
        for (int i = 0; i < str.length(); i++)
        {
            if (str[i] < 0)
                ans++;
        }
        cout << ans / 2 << endl;
    }

    return 0;
}
