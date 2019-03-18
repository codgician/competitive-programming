#include <bits/stdc++.h>
using namespace std;

#define SIZE 26

int f[SIZE], f1[SIZE];
string fst, snd;

bool check() {
    int len = fst.size(), conf = 0;
    for (int i = 0; i < len; i++) {
        if (f[fst[i] - 'a'] == -1) {
            conf++;
            int from = fst[i] - 'a', to = snd[i] - 'a';
            if (f1[to] != -1 && f1[to] != from) {
                return false;
            }
            f[from] = to;
            f1[to] = from;
        } else if (snd[i] - 'a' != f[fst[i] - 'a']) {
            return false;
        } else if (f1[snd[i] - 'a'] != fst[i] - 'a') {
            return false;
        }
    }

    if (conf == 25) {
        int from = -1, to = -1;
        for (int i = 0; i < SIZE; i++)
            if (f[i] == -1) {
                from = i;
                break;
            }
        for (int i = 0; i < SIZE; i++)
            if (f1[i] == -1) {
                to = i;
                break;
            }

        f[from] = to;
        f1[to] = from;
    }
    
    return true;
}

void print() {
    for (int i = 0; i < SIZE; i++) {
        if (f[i] != -1) {
            char from = i + 'a', to = f[i] + 'a';
            cout << from << "->" << to << endl;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    
    while (cin >> fst >> snd) {
        memset(f, -1, sizeof(f));
        memset(f1, -1, sizeof(f1));
        if (check())
            print();
        else
            cout << "Impossible" << endl;
    }
    
    return 0;
}