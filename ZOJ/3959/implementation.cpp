#include <bits/stdc++.h>
using namespace std;

#define SIZE 110

int arr[SIZE], num;

bool check() {
    if (num < 10 || num > 13)
        return false;
    sort(arr + 0, arr + num);
    if (arr[0] != 1)
        return false;
    if (arr[1] != 1)
        return false;
    for (int i = 0; i < num - 1; i++)
        arr[i] = arr[i + 1] - arr[i];
    for (int i = 0; i < num - 2; i++)
        if (arr[i] > 2)
            return false;
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
            cin >> arr[i];
        cout << (check() ? "Yes\n" : "No\n");
    }

    return 0;
}