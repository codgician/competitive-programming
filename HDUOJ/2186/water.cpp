#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <string>
#include <iomanip>
#include <climits>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    int caseNum;
    cin >> caseNum;
    while (caseNum--)
    {
        int n, ans = 0;
        cin >> n;
        int rescueNum = n / 2;
        ans += rescueNum / 10;
        if (rescueNum % 10)
            ans++;
        int firstAidNum = (n - rescueNum) * 2 / 3;
        ans += firstAidNum / 10;
        if (firstAidNum % 10)
            ans++;
        int communicateNum = n - rescueNum - firstAidNum;
        ans += communicateNum / 10;
        if (communicateNum % 10)
            ans++;
        cout << ans << endl;
    }
    return 0;
}
