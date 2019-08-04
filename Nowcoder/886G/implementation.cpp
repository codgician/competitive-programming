#include <bits/stdc++.h>
using namespace std;

#define SIZE 100010

random_device rd;
mt19937 rng(rd());

long long int encode(const string & str) {
    const auto id = [](char ch) -> int {
        return ch - 'A';
    };

    long long int ret = 0;
    for (auto & ch : str)
        if (ch != '/')
            ret = ret * 10 + id(ch);
    return ret;
}

long long int arr[SIZE];
int f[10], num;
const int monthLim[12] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

bool check(long long int rule) {
    long long int dec = 0, fac = 1;
    for (int i = 0; i < 8; i++) {
        dec += fac * f[rule % 10];
        rule /= 10; fac *= 10;
    }
    
    int day = dec % 100; dec /= 100;
    int month = dec % 100; dec /= 100;
    int year = dec;

    const auto validate = [year, month, day]() -> bool {
        const auto isLeap = [year]() -> bool {
            return (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
        };
        const auto whichDay = [year, month, day]() -> int {
            int y = year, m = month, d = day;
            if (m <= 2)
                m += 12, y--;
            int c = y / 100; y %= 100;
            int ret = (y + (y >> 2) + (c >> 2) - (c << 1) + (26 * (m + 1)) / 10 + d - 1) % 7;
            return (ret + 7) % 7;
        };

        if (year < 1600 || month > 12 || month == 0 || day == 0)
            return false;
        if (day > monthLim[month - 1])
            return false;
        if (month == 2 && day == 29 && !isLeap())
            return false;
        if (whichDay() != 5)
            return false;

        return true;
    };

    if (!validate())
        return false;
    return true;
}

bool precheck() { 
    int blk = num / 20 + 1;
    for (int i = 0; i * blk < num; i++) {
        uniform_int_distribution<int> unifInt(i * blk, min(num - 1, i * blk + blk - 1));
        if (!check(arr[unifInt(rng)]))
            return false;
    }
    return true;
}

bool fullcheck() {
    for (int i = 0; i < num; i++)
        if (!check(arr[i]))
            return false;
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int caseNum; cin >> caseNum;
    for (int t = 1; t <= caseNum; t++) {
        cin >> num;
        for (int i = 0; i < num; i++) {
            string buf; cin >> buf;
            arr[i] = encode(buf);
        }

        sort(arr + 0, arr + num);
        num = unique(arr + 0, arr + num) - arr;

        bool flag = false;
        for (int i = 0; i < 10; i++)
            f[i] = i;
        while (true) {
            if (precheck() && fullcheck()) {
                flag = true; break;
            }
            if (!next_permutation(f + 0, f + 10))
                break;
        }

        cout << "Case #" << t << ": ";
        if (flag) {
            for (int i = 0; i < 10; i++)
                cout << f[i];
            cout << '\n';
        } else {
            cout << "Impossible\n";
        }
    }

    return 0;
}