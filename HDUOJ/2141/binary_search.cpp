#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <string>
#include <iomanip>
#include <climits>
#define SIZE 501
#define SUM_SIZE 250001
using namespace std;

long long int a[SIZE], abSum[SUM_SIZE], c[SIZE];

int main()
{
    ios::sync_with_stdio(false);
    int aNum, bNum, cNum, caseNum = 1;
    while (cin >> aNum >> bNum >> cNum)
    {
        for (int i = 0; i < aNum; i++)
            cin >> a[i];
        int abSumPt = 0;
        for (int i = 0; i < bNum; i++)
        {
            long long int tmp;
            cin >> tmp;
            for (int j = 0; j < aNum; j++)
                abSum[abSumPt++] = tmp + a[j];
        }
        sort(abSum + 0, abSum + abSumPt);
        for (int i = 0; i < cNum; i++)
            cin >> c[i];

        int xNum;
        cin >> xNum;

        cout << "Case " << caseNum++ << ":" << endl;
        while (xNum--)
        {
            long long int x;
            cin >> x;
            bool ans = false;
            for (int i = 0; i < cNum; i++)
            {
                ans = binary_search(abSum + 0, abSum + abSumPt, x - c[i]);
                if (ans)
                    break;
            }
            if (ans)
                cout << "YES" << endl;
            else
                cout << "NO" << endl;
        }
    }
    return 0;
}
