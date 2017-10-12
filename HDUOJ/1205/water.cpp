#include <iostream>
#include <cstdio>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    int caseNum;
    cin >> caseNum;
    for (int t = 0; t < caseNum; t++)
    {
        int candyType, maxTypeNum = -1, tmp;
        long long sum = 0;
        cin >> candyType;
        for (int i = 0; i < candyType; i++)
        {
            cin >> tmp;
            if (tmp > maxTypeNum)
                maxTypeNum = tmp;
            sum += tmp;
        }
        if (sum - maxTypeNum + 1 >= maxTypeNum)
            cout << "Yes" << endl;
        else
            cout << "No" << endl;
    }
    return 0;
}
