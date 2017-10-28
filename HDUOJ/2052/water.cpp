#include <iostream>
#include <cstdio>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    int width, length;
    while (cin >> width >> length)
    {
        cout << "+";
        for (int i = 0; i < width; i++)
            cout << "-";
        cout << "+" << endl;
        for (int i = 0; i < length; i++)
        {
            cout << "|";
            for (int j = 0; j < width; j++)
                cout << " ";
            cout << "|" << endl;
        }
        cout << "+";
        for (int i = 0; i < width; i++)
            cout << "-";
        cout << "+" << endl << endl;
    }
    return 0;
}
