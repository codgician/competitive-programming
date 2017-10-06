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
        int num, sum = 0;
        cin >> num;
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
