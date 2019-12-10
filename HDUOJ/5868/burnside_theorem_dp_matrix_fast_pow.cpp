#include <bits/stdc++.h>
using namespace std;

#define MAT_SIZE 2
const int mod = 1e9 + 7;

class Matrix {
public:
    int row, col;
    long long int arr[MAT_SIZE][MAT_SIZE];
    Matrix(int r, int c) {
        row = r; col = c;
        memset(arr, 0, sizeof(arr));
    }

    Matrix operator * (const Matrix & snd) const {
        // assert(col == snd.row);
        Matrix ret(row, snd.col);
        for (int i = 0; i < row; i++) {
            for (int k = 0; k < col; k++) {
                long long int cnt = arr[i][k];
                for (int j = 0; j < col; j++) {
                    ret.arr[i][j] += cnt * snd.arr[k][j];
                    if (ret.arr[i][j] >= mod)
                        ret.arr[i][j] %= mod;
                }
            }
        }
        return ret;
    }
    Matrix & operator = (const Matrix & snd) {
        row = snd.row; col = snd.col;
        memcpy(arr, snd.arr, sizeof(snd.arr));
        return *this;
    }
};

Matrix matFastPow(Matrix mat, long long int n) {
    // assert(mat.row == mat.col);
    Matrix ret(mat.row, mat.col);
    for (int i = 0; i < mat.row; i++)
        ret.arr[i][i] = 1;
    while (n > 0) {
        if (n & 1)
            ret = ret * mat;
        mat = mat * mat;
        n >>= 1;
    }
    return ret;
}

long long int fastPow(long long int a, long long int n, long long int mod) {
    long long int ret = 1; a %= mod;
    while (n > 0) {
        if (n & 1)
            ret = ret * a % mod;
        a = a * a % mod; n >>= 1;
    }
    return ret;
}

long long int phi(long long int num) {
    long long int ret = num;
    for (int i = 2; 1ll * i * i <= num; i++) {
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

vector<long long int> facs;
void factorize(long long int num) {
    facs.clear();
    for (int i = 1; 1ll * i * i <= num; i++) {
        if (num % i != 0)
            continue;
        facs.push_back(i);
        if (i * i != num)
            facs.push_back(num / i);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    Matrix trans(2, 2);
    trans.arr[0][0] = 1; trans.arr[0][1] = 1;
    trans.arr[1][0] = 1; trans.arr[1][1] = 0;

    long long int n;
    while (cin >> n) {
        if (n == 1) {
            cout << 2 << '\n';
            continue;
        }
        long long int ans = 0; factorize(n);
        for (const auto & t: facs) {
            Matrix ret = matFastPow(trans, t);
            long long int cnt = 0;
            for (int i = 0; i < ret.row; i++)
                cnt = (cnt + ret.arr[i][i]) % mod;
            ans = (ans + phi(n / t) * cnt) % mod; 
        }
        ans = ans * fastPow(n, mod - 2, mod) % mod;
        cout << (ans + mod) % mod << '\n';
    }

    return 0;
}
