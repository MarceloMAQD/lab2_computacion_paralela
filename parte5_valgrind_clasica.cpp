#include <iostream>
#include <vector>
#include <random>

using namespace std;
using Matriz = vector<vector<double>>;

void multiplicacionClasica(const Matriz& A, const Matriz& B, Matriz& C) {
    int n = (int)A.size();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            double suma = 0.0;
            for (int k = 0; k < n; k++) {
                suma += A[i][k] * B[k][j];
            }
            C[i][j] = suma;
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

    mt19937 rng(42);
    Matriz A = generarMatrizAleatoria(n, rng);
    Matriz B = generarMatrizAleatoria(n, rng);
    Matriz C(n, vector<double>(n, 0.0));

    multiplicacionClasica(A, B, C);

    return 0;
}