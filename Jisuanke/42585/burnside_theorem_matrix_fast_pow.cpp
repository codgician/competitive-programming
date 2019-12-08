#include <bits/stdc++.h>
using namespace std;

#define SIZE 100010
#define MAT_SIZE 64
const int mod = 998244353;

int arr[4][4][4][4];

long long int fastPow(long long int a, long long int n, long long int mod) {
    long long int ret = 1; a %= mod;
    while (n > 0) {
        if (n & 1)
            ret = ret * a % mod;
        a = a * a % mod; n >>= 1;
    }
    return ret;
}

class Matrix {
public:
    int row, col;
    long long int arr[MAT_SIZE][MAT_SIZE];
    Matrix(int r, int c) {
        row = r; col = c;
        for (int i = 0; i < r; i++)
            for (int j = 0; j < c; j++)
                arr[i][j] = 0;
    }
    Matrix operator * (const Matrix & snd) const {
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

int minFac[SIZE], primes[SIZE], phi[SIZE], primesPt;
void initPhi() {
    memset(minFac, 0, sizeof(minFac));
    primesPt = 0; phi[1] = 1;
    for (int i = 2; i < SIZE; i++) {
        if (minFac[i] == 0) {
            phi[i] = i - 1;
            minFac[i] = i, primes[primesPt++] = i;
        }
        for (int j = 0; j < primesPt && primes[j] <= min(minFac[i], (SIZE - 1) / i); j++) {
            minFac[i * primes[j]] = primes[j];
            if (minFac[i] == primes[j])
                phi[i * primes[j]] = phi[i] * primes[j];
            else
                phi[i * primes[j]] = phi[i] * (primes[j] - 1);
        }
    }
}

int encode(int a, int b, int c) {
    return a * 16 + b * 4 + c;
}

vector<int> facs;
void factorize(int n) {
    facs.clear();
    for (int i = 1; i * i <= n; i++) {
        if (n % i != 0)
            continue;
        facs.push_back(i);
        if (i * i != n)
            facs.push_back(n / i);    
    }
}

Matrix trans(64, 64);

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    initPhi(); 
    
    int len, banNum;
    cin >> len >> banNum;
    for (int a = 0; a < 4; a++)
        for (int b = 0; b < 4; b++)
            for (int c = 0; c < 4; c++)
                for (int d = 0; d < 4; d++)
                    arr[a][b][c][d] = 1;
    while (banNum--) {
        int a, b, c, d; cin >> a >> b >> c >> d;
        arr[a][b][c][d] = 0;
    }

    for (int a = 0; a < 4; a++) {
        for (int b = 0; b < 4; b++) {
            for (int c = 0; c < 4; c++) {
                int st = encode(a, b, c);
                for (int k = 0; k < 4; k++)
                    trans.arr[st][encode(k, a, b)] = arr[k][a][b][c];
            }
        }
    }

    long long int ans = 0;
    factorize(len);

    for (const auto t : facs) {
        long long int cnt = 0;
        auto ret = matFastPow(trans, t);
        for (int i = 0; i < MAT_SIZE; i++)
            cnt = (cnt + ret.arr[i][i]) % mod;
        ans = (ans + cnt * phi[len / t] % mod) % mod;
    }

    cout << ans * fastPow(len, mod - 2, mod) % mod << '\n';
    return 0;
}
