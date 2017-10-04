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
        int negNum = 0, posNum = 0, zeroNum = 0;
        for (int i = 0; i < num; i++)
        {
            double tmp;
            cin >> tmp;

            if (tmp > 0)
                posNum ++;
            else if (tmp < 0)
                negNum ++;
            else
                zeroNum ++;
        }
        cout << negNum << " " << zeroNum << " " << posNum << endl;
    }
    return 0;
}
