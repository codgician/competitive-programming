#include <iostream>
#include <cstdio>
#define SIZE 100010
using namespace std;

int arr[SIZE];

int main()
{
    ios::sync_with_stdio(false);
    arr[1] = 1;
    arr[2] = 1;
    cout << "#1: " << arr[1] << endl << "#2: " << arr[2] << endl;
    for (int i = 3; i < SIZE; i++)
    {
        bool flag = false;
        arr[i] = (arr[i - 1] + arr[i - 2]) % 26;
        cout << "#" << i << ": " << arr[i] << endl;
        for (int j = 2; j < i; j++)
        {
            if (arr[i] == arr[j] && arr[i - 1] == arr[j - 1])
            {
                cout << "cycStart: " << j - 1 << " cycEnd: " << i - 2 << endl;
                flag = true;
                break;
            }
        }
        if (flag)
            break;
    }

    return 0;
}
