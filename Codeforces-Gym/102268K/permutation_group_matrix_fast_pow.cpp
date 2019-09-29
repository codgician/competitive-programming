#include <bits/stdc++.h>
using namespace std;

#define SIZE 12
const int mod = 998244353;

class Matrix {
public:
    int row, col;
    long long int arr[SIZE][SIZE];

    Matrix(int r, int c) {
        row = r; col = c;
        memset(arr, 0, sizeof(arr));
    }

    void operator += (const Matrix & b) {
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                arr[i][j] += b.arr[i][j];
                if (arr[i][j] >= mod)
                    arr[i][j] %= mod;
            }
        }
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

int mp[SIZE][SIZE];
vector<vector<int> > permus;
vector<int> a = {1, 0, 3, 2}, b = {1, 2, 0, 3};

vector<int> compose(const vector<int> & fst, const vector<int> & snd) {
    vector<int> ret; ret.resize(4);
    for (int i = 0; i < 4; i++)
        ret[i] = fst[snd[i]];
    return ret;
}

int id(const vector<int> & vec) {
    int ret = 0, fac = 1, len = vec.size();
    for (int i = len - 1; i >= 0; i--) {
        int cnt = 0;
        for (int j = i + 1; j < len; j++)
            cnt += (vec[i] > vec[j]);
        ret += cnt * fac; fac *= (len - i);
    }
    return (ret >> 1);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    vector<int> v = {0, 1, 2, 3};
    for (int i = 0; i < (SIZE << 1); next_permutation(v.begin(), v.end()), i++)
        if ((i & 3) == 0 || (i & 3) == 3)
            permus.push_back(v);

    Matrix trans(12, 12), base(12, 1); base.arr[0][0] = 1;
    for (int i = 0; i < 12; i++) {
        trans.arr[id(compose(permus[i], a))][i]++;
        trans.arr[id(compose(permus[i], b))][i]++;
    }
    
    string str; int len; cin >> len >> str >> len;
    v = permus[0];
    for (const auto & ch : str)
        v = compose(v, ch == 'a' ? a : b);
    
    cout << (matFastPow(trans, len) * base).arr[id(v)][0] << '\n';
    return 0;
}