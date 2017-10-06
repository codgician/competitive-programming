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
        int a, b;
        cin >> a >> b;
        cout << a + b << endl;
    }
    return 0;
}
