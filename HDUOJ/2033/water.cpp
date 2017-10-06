#include <iostream>
#include <cstdio>
using namespace std;

struct Node {
    int second;
    int minute;
    int hour;
} a, b, c;

int main()
{
    ios::sync_with_stdio(false);
    int caseNum;
    cin >> caseNum;
    for (int t = 0; t < caseNum; t++)
    {
        int carry;
        cin >> a.hour >> a.minute >> a.second >> b.hour >> b.minute >> b.second;
        c.second = a.second + b.second;
        carry = c.second / 60;
        c.second %= 60;
        c.minute = a.minute + b.minute + carry;
        carry = c.minute / 60;
        c.minute %= 60;
        c.hour = a.hour + b.hour + carry;
        cout << c.hour << " " << c.minute << " " << c.second << endl;
    }
    return 0;
}
