#include <bits/stdc++.h>
using namespace std;

#define SIZE 110

long long int req[SIZE], hav[SIZE];
int num;

bool check() {
    long long int extra = 0;
    for (int i = num - 1; i >= 0; i--) {
        if (req[i] > hav[i] + extra)
            return false;
        extra += hav[i] - req[i];
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int caseNum;
    cin >> caseNum;
    while (caseNum--) {
        cin >> num;
        for (int i = 0; i < num; i++)
            cin >> req[i];
        for (int i = 0; i < num; i++)
            cin >> hav[i];

        if (check())
            cout << "Yes\n";
        else
            cout << "No\n";
    }

    return 0;
}