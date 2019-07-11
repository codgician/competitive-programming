#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

#define SIZE 11

const int mod = 9973;

typedef struct _Matrix {
    long long int arr[SIZE][SIZE];
    int row, column;
    _Matrix(int pRow, int pColumn) {
        row = pRow;
        column = pColumn;
        memset(arr, 0, sizeof(arr));
    }
    _Matrix & operator + (const _Matrix & b) {
        // assert(row == b.row && column == b.column);
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < column; j++) {
                arr[i][j] += b.arr[i][j];
                if (arr[i][j] >= mod)
                    arr[i][j] -= mod;
            }
        }
        return *this;
    }
    _Matrix operator * (const _Matrix & b) const {
        // assert(column == b.row);
        _Matrix ans(row, b.column);
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < b.column; j++) {
                for (int k = 0; k < column; k++)
                    ans.arr[i][j] += (arr[i][k] * b.arr[k][j]);
                if (ans.arr[i][j] >= mod)
                    ans.arr[i][j] %= mod;
            }
        }
        return ans;
    }
    _Matrix & operator = (const _Matrix & b) {
        memcpy(arr, b.arr, sizeof(b.arr));
        return *this;
    }
} Matrix;

Matrix matrixFastPow(Matrix matrix, long long int n) {
    // assert(matrix.row == matrix.column);
    Matrix ans(matrix.row, matrix.column);
    for (int i = 0; i < matrix.row; i++)
        ans.arr[i][i] = 1;
    while (n > 0) {
        if (n & 1)
            ans = ans * matrix;
        matrix = matrix * matrix;
        n >>= 1;
    }
    return ans;
}

long long int invArr[mod];

void initInv() {
    invArr[1] = 1; invArr[0] = 0;
    for (int i = 2; i < mod; i++)
        invArr[i] = (mod - mod / i) * invArr[mod % i] % mod;
}

vector<int> fac;

void getFac(int num) {
    fac.clear();
    for (int i = 1; i * i <= num; i++) {
        if (num % i != 0)
            continue;
        fac.push_back(i);
        if (i * i != num)
            fac.push_back(num / i);
    }
}

int phi(int num) {
    int ret = num;
    for (int i = 2; i * i <= num; i++) {
        if (num % i != 0)
            continue;
        ret -= ret / i;
        while (num % i == 0)
            num /= i;
    }
    if (num > 1)
        ret -= ret / num;
    return ret;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    initInv();
    int caseNum; cin >> caseNum;
    while (caseNum--) {
        int len, num, rest;
        cin >> len >> num >> rest;

        Matrix trans(num, num);
        for (int i = 0; i < num; i++)
            for (int j = 0; j < num; j++)
                trans.arr[i][j] = 1;
        while (rest--) {
            int fst, snd; cin >> fst >> snd;
            fst--; snd--;
            trans.arr[fst][snd] = 0;
            trans.arr[snd][fst] = 0;
        }

        Matrix ret(num, num);
        int ans = 0; getFac(len);
        for (int t = 0; t < (int)fac.size(); t++) {
            int cnt = fac[t], cntAns = 0, cntPhi = phi(len / cnt) % mod;
            ret = matrixFastPow(trans, cnt);
            for (int i = 0; i < num; i++) {
                cntAns += ret.arr[i][i];
                if (cntAns >= mod)
                    cntAns -= mod;
            }
            ans += cntAns * cntPhi % mod;
            if (ans >= mod)
                ans -= mod;
        }

        ans = ans * invArr[len % mod] % mod;
        cout << ans << '\n';
    }

    return 0;
}