#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <string>
#include <iomanip>
#include <climits>
#include <vector>
#include <set>
#include <queue>
#include <map>
using namespace std;

map <string, string> mp;

int main()
{
    ios::sync_with_stdio(false);
    int serverNum, commandNum;
    cin >> serverNum >> commandNum;
    for (int i = 0; i < serverNum; i++)
    {
        string name, ip;
        cin >> name >> ip;
        mp[ip] = name;
    }
    for (int i = 0; i < commandNum; i++)
    {
        string command, ip;
        cin >> command >> ip;
        ip = ip.substr(0, ip.length() - 1);
        cout << command << " " << ip << "; #" << mp[ip] << endl;
    }
    return 0;
}
