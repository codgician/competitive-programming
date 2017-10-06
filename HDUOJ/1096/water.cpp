#include <iostream>
#include <cstdio>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    int caseNum;
    cin >> caseNum;
    for (int i = 0; i < caseNum; i++)
    {
        int num;
        cin >> num;
        int sum = 0;
        for (int i = 0; i < num; i++)
        {
            int tmp;
            cin >> tmp;
            sum += tmp;
        }
        cout << sum << endl;
        if (i != caseNum - 1)
            cout << endl;
    }
    return 0;
}
