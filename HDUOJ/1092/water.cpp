#include <iostream>
#include <cstdio>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    int num;
    while (cin >> num)
    {
        if (num == 0)
            break;
        int sum = 0;
        for (int i = 0; i < num; i++)
        {
            int tmp;
            cin >> tmp;
            sum += tmp;
        }
        cout << sum << endl;
    }
    return 0;
}
