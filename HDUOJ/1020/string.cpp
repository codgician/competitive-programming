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
        string str;
        cin >> str;
        int counter = 1, i;
        char prevChar = str[0];
        for (i = 1; i < str.length(); i++)
        {
            if (str[i] == prevChar)
                counter++;
            else
            {
                if (counter == 1)
                    cout << str[i - 1];
                else
                {
                    cout << counter << str[i - 1];
                    counter = 1;
                }
                prevChar = str[i];
            }
        }
        if (counter > 1)
            cout << counter << str[i - 1];
        else
            cout << str[i - 1];
        cout << endl;
    }
    return 0;
}
