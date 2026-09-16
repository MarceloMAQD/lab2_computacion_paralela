#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <random>

using namespace std;
using Clock = chrono::high_resolution_clock;
using Matriz = vector<vector<double>>;


double multiplicacionClasica(const Matriz& A, const Matriz& B, Matriz& C) {
    int n = (int)A.size();

    auto inicio = Clock::now();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            double suma = 0.0;
            for (int k = 0; k < n; k++) {
                suma += A[i][k] * B[k][j];
            }
            C[i][j] = suma;
        }
    }
    auto fin = Clock::now();

    return chrono::duration<double>(fin - inicio).count();
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
    vector<int> tamanos = {64, 128, 256, 512, 1024, 1536};

    const int repeticiones = 2;

    ofstream csv("resultados_mult_clasica.csv");
    csv << "tamano,tiempo\n";

    mt19937 rng(42);

    for (int n : tamanos) {
        Matriz A = generarMatrizAleatoria(n, rng);
        Matriz B = generarMatrizAleatoria(n, rng);
        Matriz C(n, vector<double>(n, 0.0));

        double tiempoTotal = 0.0;
        for (int r = 0; r < repeticiones; r++) {
            tiempoTotal += multiplicacionClasica(A, B, C);
        }
        double tiempoProm = tiempoTotal / repeticiones;

        cout << "n=" << n << "  tiempo=" << tiempoProm << "s\n";
        csv << n << "," << tiempoProm << "\n";
    }

    csv.close();
    return 0;
}