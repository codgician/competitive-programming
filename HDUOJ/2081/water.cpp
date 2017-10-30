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
        long long int phoneNum;
        cin >> phoneNum;
        cout << 600000 + phoneNum % 100000 << endl;
    }
    return 0;
}
