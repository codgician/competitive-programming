// Cycle is found using helper.cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#define SIZE 85
using namespace std;

int arr[SIZE];

void init()
{
    arr[1] = 1;
    arr[2] = 1;
    for (int i = 3; i < SIZE; i++)
        arr[i] = (arr[i - 1] + arr[i - 2]) % 26;
}

int main()
{
    ios::sync_with_stdio(false);
    init();
    string str;
    while (getline(cin, str))
    {
        int counter = 1;
        for (int i = 0; i < str.length(); i++)
        {
            if (str[i] >= 'A' && str[i] <= 'Z')
            {
                str[i] += arr[counter % 84];
                if (str[i] > 'Z')
                    str[i] -= 26;
                counter++;
            }
        }

        cout << str << endl;
    }
    return 0;
}
