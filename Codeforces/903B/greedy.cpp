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
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    int vovaHealth, vovaAttack, potion;
    cin >> vovaHealth >> vovaAttack >> potion;
    int monsHealth, monsAttack;
    cin >> monsHealth >> monsAttack;

    int monsDie = monsHealth / vovaAttack;
    if (monsHealth % vovaAttack > 0)
        monsDie++;
    int needHealth = monsAttack * (monsDie - 1);

    int healNum = 0;
    if (vovaHealth <= needHealth)
    {
        healNum += (needHealth - vovaHealth + 1) / (potion - monsAttack);
        if ((needHealth - vovaHealth + 1) % (potion - monsAttack) > 0)
            healNum++;
    }

    cout << monsDie + healNum << endl;
    for (int i = 0; i < healNum; i++)
    {
        cout << "HEAL" << endl;
    }
    for (int i = 0; i < monsDie; i++)
    {
        cout << "STRIKE" << endl;
    }
    return 0;
}
