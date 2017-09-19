// Emulation
// b stands for balloon, c stands for color.

#include <iostream>
#include <string>
#define MAXN 1010
using namespace std;

string cArr[MAXN];
int cCountArr[MAXN];

int main()
{
    while (true)
    {
        int bCount, cCount = 0, maxCount = 0;
        string maxColor;
        cin >> bCount;
        if (bCount == 0)
            break;

        for (int i = 0; i < bCount; i++)
        {
            string c;
            cin >> c;
            if (cCount == 0)
            {
                cArr[0] = c;
                cCountArr[0] = 1;
                cCount = 1;
            }
            else {
                bool flag = false;
                for (int j = 0; j < cCount; j++)
                {
                    if (cArr[j] == c)
                    {
                        cCountArr[j]++;
                        flag = true;
                        break;
                    }
                }

                if (flag == false)
                {
                    cArr[cCount] = c;
                    cCountArr[cCount] = 1;
                    cCount++;
                }
            }
        }

        for (int i = 0; i < cCount; i++)
        {
            if (cCountArr[i] > maxCount)
            {
                maxColor = cArr[i];
                maxCount = cCountArr[i];
            }
        }

        cout << maxColor << endl;
    }
    return 0;
}
