#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    int scr;
    while(cin >> scr)
    {
        if (scr < 0 || scr > 100)
            cout << "Score is error!" << endl;
        else
        {
            if (scr >= 90)
                cout << "A" << endl;
            else if (scr >= 80 && scr < 90)
                cout << "B" << endl;
            else if (scr >= 70 && scr < 80)
                cout << "C" << endl;
            else if (scr >= 60 && scr < 69)
                cout << "D" << endl;
            else
                cout << "E" << endl;
        }
    }
    return 0;
}