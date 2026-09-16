#include <iostream>
#include <vector>
#include <random>
#include <algorithm>

using namespace std;
using Matriz = vector<vector<double>>;

void multiplicacionPorBloques(const Matriz& A, const Matriz& B, Matriz& C, int bs) {
    int n = (int)A.size();

    for (int ii = 0; ii < n; ii += bs) {
        for (int jj = 0; jj < n; jj += bs) {
            for (int kk = 0; kk < n; kk += bs) {

                int iMax = min(ii + bs, n);
                int jMax = min(jj + bs, n);
                int kMax = min(kk + bs, n);

                for (int i = ii; i < iMax; i++) {
                    for (int j = jj; j < jMax; j++) {
                        double suma = C[i][j];
                        for (int k = kk; k < kMax; k++) {
                            suma += A[i][k] * B[k][j];
                        }
                        C[i][j] = suma;
                    }
                }

            }
        }
    }
}

Matriz generarMatrizAleatoria(int n, mt19937& rng) {
    uniform_real_distribution<double> dist(0.0, 1.0);
    Matriz M(n, vector<double>(n));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            M[i][j] = dist(rng);
    return M;
}

int main() {
    const int n = 512;
    const int bs = 128;

    mt19937 rng(42);
    Matriz A = generarMatrizAleatoria(n, rng);
    Matriz B = generarMatrizAleatoria(n, rng);
    Matriz C(n, vector<double>(n, 0.0));

    multiplicacionPorBloques(A, B, C, bs);

    return 0;
}